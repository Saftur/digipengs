/**
 * @file Map.c
 * @author Arthur Bouvier
 * @date 2/5/2019
 * @brief Map implementation
 */
#include "stdafx.h"
#include "Map.h"

#include <stdio.h>
#include "vector.h"

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
