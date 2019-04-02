/**
 * @file Map.c
 * @author Arthur Bouvier
 * @date 2/5/2019
 * @brief Map implementation
 */
#include "stdafx.h"
#include "Map.h"

#include <AEEngine.h>
#include <stdio.h>
#include "vector.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Utils.h"

#define CAM_STRAIGHT_ROT_LERP 0.2f
#define CAM_TURN_ROT_LERP 0.2f
#define CAM_BETWEEN_ROT_LERP(percentOfStraight) (CAM_STRAIGHT_ROT_LERP * percentOfStraight + CAM_TURN_ROT_LERP * (1-percentOfStraight))

static Tile tiles[MAP_MAX_SIZE][MAP_MAX_SIZE];

static unsigned width, height;
static unsigned startX, startY;

void Map_load(const char *filename, Tile tilemap[MAP_MAX_SIZE][MAP_MAX_SIZE], 
                 unsigned *w, unsigned *h, unsigned *sx, unsigned *sy) {
    FILE *file;
    fopen_s(&file, filename, "rt");
    if (!file)
        return;
    *w = 1;
    int c;
    unsigned x = 0, y = 0;
    int which = 0;

    char startPosStrX[8];
    char startPosStrY[8];
    char *spPtr = startPosStrX;
    while ((c = fgetc(file)) != EOF) {
        if (c == ' ') {
            *spPtr = 0;
            spPtr = startPosStrY;
        } else if (c == '\n') {
            *spPtr = 0;
            break;
        } else if (c >= '0' && c <= '9')
            *(spPtr++) = (char)c;
    }
    *sx = atoi(startPosStrX);
    *sy = atoi(startPosStrY);

    while ((c = fgetc(file)) != EOF) {
        if (which > 1) {
            Tile *t = &tilemap[y][x];
            if (t->from == SNone)
                t->type = TTNone;
            else if (t->from == SLeft && t->to == SRight ||
                     t->from == SRight && t->to == SLeft)
                t->type = TTHoriz;
            else if (t->from == SUp && t->to == SDown ||
                     t->from == SDown && t->to == SUp)
                t->type = TTVert;
            else t->type = TTTurn;
            t->x = x;
            t->y = y;
            t->isStart = 0;
            x++;
            which = 0;
            if (x > *w)
                *w = x;
        }
        switch (c) {
        case 'L':
            if (which)
                tilemap[y][x].to = SLeft;
            else tilemap[y][x].from = SLeft;
            which++;
            break;
        case 'R':
            if (which)
                tilemap[y][x].to = SRight;
            else tilemap[y][x].from = SRight;
            which++;
            break;
        case 'U':
            if (which)
                tilemap[y][x].to = SUp;
            else tilemap[y][x].from = SUp;
            which++;
            break;
        case 'D':
            if (which)
                tilemap[y][x].to = SDown;
            else tilemap[y][x].from = SDown;
            which++;
            break;
        case 'N':
            if (which)
                tilemap[y][x].to = SNone;
            else tilemap[y][x].from = SNone;
            which++;
            break;
        case '\n':
            if (x > 0) {
                y++;
                x = 0;
                which = 0;
            }
            break;
        }
    }
    fclose(file);
    if (which > 1) {
        Tile *t = &tilemap[y][x];
        if (t->from == SNone)
            t->type = TTNone;
        else if (t->from == SLeft && t->to == SRight ||
            t->from == SRight && t->to == SLeft)
            t->type = TTHoriz;
        else if (t->from == SUp && t->to == SDown ||
            t->from == SDown && t->to == SUp)
            t->type = TTVert;
        else t->type = TTTurn;
        t->x = x;
        t->y = y;
        t->isStart = 0;
    }
    tilemap[*sy][*sx].isStart = 1;
    if (x > 0)
        y++;
    *h = y;
}

void Map_init(const char *filename) {
    Map_load(filename, tiles, &width, &height, &startX, &startY);
}

static void _updateCamera(Camera *cam, AEVec2 pos, int lerp) {
    unsigned tx, ty;
    Map_worldPosToTilePos(&tx, &ty, pos.x, pos.y);
    float twx, twy;
    Map_tilePosToWorldPos(&twx, &twy, tx, ty);
    Tile tile = Map_getTile(tx, ty);
    Tile nextTile = Map_getNextTile(tile);
    Tile prevTile = Map_getPrevTile(tile);
    Tile prevPrevTile = Map_getPrevTile(prevTile);

    switch (tile.type) {
    case TTHoriz:
        cam->worldPos.x = pos.x;
        cam->worldPos.y = twy;
        if (lerp)
            cam->worldRot = deg_lerpf(cam->worldRot, (tile.from == SLeft ? 90.f : -90.f),
                                      prevTile.type == TTTurn ? CAM_BETWEEN_ROT_LERP(0.5f) : 
                                      prevPrevTile.type == TTTurn ? CAM_BETWEEN_ROT_LERP(0.75f) : CAM_STRAIGHT_ROT_LERP);
        else
            cam->worldRot = (tile.from == SLeft ? 90.f : -90.f);
        break;
    case TTVert:
        cam->worldPos.x = twx;
        cam->worldPos.y = pos.y;
        if (lerp)
            cam->worldRot = deg_lerpf(cam->worldRot, (tile.from == SDown ? 0.f : 180.f), 
                                      prevTile.type == TTTurn ? CAM_BETWEEN_ROT_LERP(0.5f) : 
                                      prevPrevTile.type == TTTurn ? CAM_BETWEEN_ROT_LERP(0.75f) : CAM_STRAIGHT_ROT_LERP);
        else
            cam->worldRot = (tile.from == SDown ? 0.f : 180.f);
        break;
    case TTTurn: {
        AEVec2 localPos;
        AEVec2 point;
        float addAngle = 0;
        if (tile.from == SRight && tile.to == SDown ||
            tile.from == SDown && tile.to == SRight) {
            point.x = twx + TILE_SIZE / 2.f;
            point.y = twy - TILE_SIZE / 2.f;
            if (tile.from == SDown)
                addAngle = 180;
        }
        if (tile.from == SLeft && tile.to == SDown ||
            tile.from == SDown && tile.to == SLeft) {
            point.x = twx - TILE_SIZE / 2.f;
            point.y = twy - TILE_SIZE / 2.f;
            if (tile.from == SLeft)
                addAngle = 180;
        }
        if (tile.from == SRight && tile.to == SUp ||
            tile.from == SUp && tile.to == SRight) {
            point.x = twx + TILE_SIZE / 2.f;
            point.y = twy + TILE_SIZE / 2.f;
            if (tile.from == SRight)
                addAngle = 180;
        }
        if (tile.from == SLeft && tile.to == SUp ||
            tile.from == SUp && tile.to == SLeft) {
            point.x = twx - TILE_SIZE / 2.f;
            point.y = twy + TILE_SIZE / 2.f;
            if (tile.from == SUp)
                addAngle = 180;
        }
        AEVec2Sub(&localPos, &pos, &point);
        AEVec2Scale(&localPos, &localPos, (TILE_SIZE / 2.f) / AEVec2Length(&localPos));
        AEVec2Add(&point, &localPos, &point);
        cam->worldPos = point;
        float rot = addAngle - AERadToDeg(AEVec2AngleFromVec2(&localPos));
        if (lerp)
            cam->worldRot = deg_lerpf(cam->worldRot, rot, nextTile.type == TTTurn ? CAM_TURN_ROT_LERP : CAM_BETWEEN_ROT_LERP(0.5f));
        else
            cam->worldRot = rot;
        break;
    }
    }
}

void Map_initCamera(Camera *cam, AEVec2 pos) {
    _updateCamera(cam, pos, 0);
}

void Map_updateCamera(Camera *cam, AEVec2 pos) {
    _updateCamera(cam, pos, 1);
}

void Map_draw()
{
    Map_customDraw(tiles, height, width);
}

void Map_customDraw(Tile tilemap[MAP_MAX_SIZE][MAP_MAX_SIZE], unsigned tilemap_height, unsigned tilemap_width)
{    
    for (unsigned y = 0; y < tilemap_height; y++) {
        for (unsigned x = 0; x < tilemap_width; x++) {
            AEVec2 worldPos;
            float worldX;
            float worldY;
            Map_tilePosToWorldPos(&worldX, &worldY, x, y);
            worldPos.x = worldX;
            worldPos.y = worldY;

            Tile tile = tilemap[y][x];
            switch (tile.from) {
            case SDown:
                switch (tile.to) {
                case SUp:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), tile.isStart ? TEXTURES.map_startTile : TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 0, 1);
                    break;
                case SRight:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_rightCornerTile, worldPos, TILE_SIZE, TILE_SIZE, 0, 1);
                    break;
                case SLeft:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_leftCornerTile, worldPos, TILE_SIZE, TILE_SIZE, 0, 1);
                    break;
                }
                break;
            case SLeft:
                switch (tile.to) {
                case SUp:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_leftCornerTile, worldPos, TILE_SIZE, TILE_SIZE, 270 * (PI / 180), 1);
                    break;
                case SRight:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), tile.isStart ? TEXTURES.map_startTile : TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 270 * (PI / 180), 1);
                    break;
                case SDown:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_rightCornerTile, worldPos, TILE_SIZE, TILE_SIZE, 270 * (PI / 180), 1);
                    break;
                }
                break;
            case SUp:
                switch (tile.to) {
                case SLeft:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_rightCornerTile, worldPos, TILE_SIZE, TILE_SIZE, 180 * (PI / 180), 1);
                    break;
                case SRight:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_leftCornerTile, worldPos, TILE_SIZE, TILE_SIZE, 180 * (PI / 180), 1);
                    break;
                case SDown:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), tile.isStart ? TEXTURES.map_startTile : TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 180 * (PI / 180), 1);
                    break;
                }
                break;
            case SRight:
                switch (tile.to) {
                case SLeft:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), tile.isStart ? TEXTURES.map_startTile : TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 90 * (PI / 180), 1);
                    break;
                case SUp:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_rightCornerTile, worldPos, TILE_SIZE, TILE_SIZE, 90 * (PI / 180), 1);
                    break;
                case SDown:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_leftCornerTile, worldPos, TILE_SIZE, TILE_SIZE, 90 * (PI / 180), 1);
                    break;
                }
                break;
            }
        }
    }
}

void Map_worldPosToTilePos(unsigned *tx, unsigned *ty, float wx, float wy) {
    *tx = (unsigned)(wx / TILE_SIZE);
    *ty = (unsigned)(-wy / TILE_SIZE);
}

void Map_tilePosToWorldPos(float *wx, float *wy, unsigned tx, unsigned ty) {
    *wx = ((float)tx + 0.5f) * TILE_SIZE;
    *wy = -((float)ty + 0.5f) * TILE_SIZE;
}

Tile Map_getTile(unsigned x, unsigned y) {
    if (x >= width || y >= height)
        return (Tile) { SNone, SNone, TTNone };
    return tiles[y][x];
}

Tile Map_getStartTile() {
    return tiles[startY][startX];
}

Tile Map_getNextTile(Tile tile) {
    return tile.to == SLeft  ? tiles[tile.y][tile.x - 1] : 
           tile.to == SRight ? tiles[tile.y][tile.x + 1] :
           tile.to == SUp    ? tiles[tile.y - 1][tile.x] :
           tile.to == SDown  ? tiles[tile.y + 1][tile.x] : 
           tile;
}

Tile Map_getPrevTile(Tile tile) {
    return tile.from == SLeft  ? tiles[tile.y][tile.x - 1] : 
           tile.from == SRight ? tiles[tile.y][tile.x + 1] :
           tile.from == SUp    ? tiles[tile.y - 1][tile.x] :
           tile.from == SDown  ? tiles[tile.y + 1][tile.x] : 
           tile;
}

unsigned Map_getWidth() {
    return width;
}

unsigned Map_getHeight() {
    return height;
}

unsigned Map_getStartX() {
    return startX;
}

unsigned Map_getStartY() {
    return startY;
}
