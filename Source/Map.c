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

#define CAM_ROT_LERP_PERCENT 0.4f

static Tile tiles[MAP_MAX_SIZE][MAP_MAX_SIZE];

static unsigned width, height;

void Map_init(const char *filename) {
    FILE *file;
    fopen_s(&file, filename, "rt");
    if (!file)
        return;
    width = 1;
    int c;
    unsigned x = 0, y = 0;
    int which = 0;
    while ((c = fgetc(file)) != EOF) {
        if (which > 1) {
            Tile *t = &tiles[y][x];
            if (t->from == SLeft && t->to == SRight ||
                t->from == SRight && t->to == SLeft)
                t->type = TTHoriz;
            else if (t->from == SUp && t->to == SDown ||
                t->from == SDown && t->to == SUp)
                t->type = TTVert;
            else t->type = TTTurn;
            x++;
            which = 0;
            if (x > width)
                width = x;
        }
        switch (c) {
        case 'L':
            if (which)
                tiles[y][x].to = SLeft;
            else tiles[y][x].from = SLeft;
            which++;
            break;
        case 'R':
            if (which)
                tiles[y][x].to = SRight;
            else tiles[y][x].from = SRight;
            which++;
            break;
        case 'U':
            if (which)
                tiles[y][x].to = SUp;
            else tiles[y][x].from = SUp;
            which++;
            break;
        case 'D':
            if (which)
                tiles[y][x].to = SDown;
            else tiles[y][x].from = SDown;
            which++;
            break;
        case 'N':
            if (which)
                tiles[y][x].to = SNone;
            else tiles[y][x].from = SNone;
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
        Tile *t = &tiles[y][x];
        if (t->from == SLeft && t->to == SRight ||
            t->from == SRight && t->to == SLeft)
            t->type = TTHoriz;
        else if (t->from == SUp && t->to == SDown ||
            t->from == SDown && t->to == SUp)
            t->type = TTVert;
        else t->type = TTTurn;
    }
    if (x > 0)
        y++;
    height = y;
}

static void _updateCamera(Camera *cam, AEVec2 pos, int lerp) {
    unsigned tx, ty;
    Map_worldPosToTilePos(&tx, &ty, pos.x, pos.y);
    float twx, twy;
    Map_tilePosToWorldPos(&twx, &twy, tx, ty);
    Tile tile = Map_getTile(tx, ty);

    switch (tile.type) {
    case TTHoriz:
        cam->worldPos.x = pos.x;
        cam->worldPos.y = twy;
        if (lerp)
            cam->worldRot = deg_lerpf(cam->worldRot, (tile.from == SLeft ? 90.f : -90.f), CAM_ROT_LERP_PERCENT);
        else
            cam->worldRot = (tile.from == SLeft ? 90.f : -90.f);
        break;
    case TTVert:
        cam->worldPos.x = twx;
        cam->worldPos.y = pos.y;
        if (lerp)
            cam->worldRot = deg_lerpf(cam->worldRot, (tile.from == SDown ? 0.f : 180.f), CAM_ROT_LERP_PERCENT);
        else
            cam->worldRot = (tile.from == SDown ? 0.f : 180.f);
        break;
    case TTTurn: {
        AEVec2 localPos;
        AEVec2 point;
        if (tile.from == SRight && tile.to == SDown ||
            tile.from == SDown && tile.to == SRight) {
            point.x = twx + TILE_SIZE / 2.f;
            point.y = twy - TILE_SIZE / 2.f;
        }
        if (tile.from == SLeft && tile.to == SDown ||
            tile.from == SDown && tile.to == SLeft) {
            point.x = twx - TILE_SIZE / 2.f;
            point.y = twy - TILE_SIZE / 2.f;
        }
        if (tile.from == SRight && tile.to == SUp ||
            tile.from == SUp && tile.to == SRight) {
            point.x = twx + TILE_SIZE / 2.f;
            point.y = twy + TILE_SIZE / 2.f;
        }
        if (tile.from == SLeft && tile.to == SUp ||
            tile.from == SUp && tile.to == SLeft) {
            point.x = twx - TILE_SIZE / 2.f;
            point.y = twy + TILE_SIZE / 2.f;
        }
        AEVec2Sub(&localPos, &pos, &point);
        AEVec2Scale(&localPos, &localPos, (TILE_SIZE / 2.f) / AEVec2Length(&localPos));
        AEVec2Add(&point, &localPos, &point);
        //AEVec2Lerp(&point, &cam->worldPos, &point, 0.1f);
        cam->worldPos = point;
        //AEVec2Add(&cam->worldPos, &localPos, &point);
        float rot = -AERadToDeg(AEVec2AngleFromVec2(&localPos));
        if (lerp)
            cam->worldRot = deg_lerpf(cam->worldRot, rot, CAM_ROT_LERP_PERCENT);
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
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            AEVec2 worldPos;
            float worldX;
            float worldY;
            Map_tilePosToWorldPos(&worldX, &worldY, x, y);
            worldPos.x = worldX;
            worldPos.y = worldY;
            
            Tile tile = Map_getTile(x, y);
            switch (tile.from) {
            case SDown:
                switch (tile.to) {
                case SUp:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 0, 1);
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
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 270 * (PI / 180), 1);
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
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 180 * (PI / 180), 1);
                    break;
                }
                break;
            case SRight:
                switch (tile.to) {
                case SLeft:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 90 * (PI / 180), 1);
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
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 0, 1);
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
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 270 * (PI / 180), 1);
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
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 180 * (PI / 180), 1);
                    break;
                }
                break;
            case SRight:
                switch (tile.to) {
                case SLeft:
                    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.map_straightTile, worldPos, TILE_SIZE, TILE_SIZE, 90 * (PI / 180), 1);
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

unsigned Map_getWidth() {
    return width;
}

unsigned Map_getHeight() {
    return height;
}
