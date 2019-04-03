/**
 * @file Map.h
 * @author Arthur Bouvier
 * @date 2/5/2019
 * @brief Map interface
 */
#pragma once

#include "Camera.h"
#include <AEVec2.h>


#define MAP_MAX_SIZE 16

#define TILE_SIZE 350

#define LANE_WIDTH ((float)TILE_SIZE / 8.f)

/**
 * @brief A side of a tile
 */
typedef enum {
    SNone, SLeft, SRight, SUp, SDown
} Side;

/**
 * @brief Type of tile
 */
typedef enum {
    TTNone, TTVert, TTHoriz, TTTurn
} TileType;

/**
 * @brief A Tile
 */
typedef struct Tile {
    Side from;      ///< Side path comes from
    Side to;        ///< Side path goes to
    TileType type;  ///< Tile type
    int isStart;    ///< Is start tile
    unsigned x, y;  ///< Tile position
    unsigned tileNum; ///< Number of this tile in the map.
} Tile;

void Map_load(const char *filename, Tile tilemap[MAP_MAX_SIZE][MAP_MAX_SIZE], 
              unsigned *width, unsigned *height, unsigned *startX, unsigned *startY);

/**
 * @brief Get number of tiles in the map.
 * @return Number of tiles in the map.
 */
unsigned Map_NumTiles();

/**
 * @brief Initialize map
 * @param filename Name of map file
 */
void Map_init(const char *filename);

void Map_initCamera(Camera *cam, AEVec2 pos, float playerDir);

void Map_updateCamera(Camera *cam, AEVec2 pos, float playerDir);

/**
 * @brief Draw the map.
 */
void Map_draw();

/**
 * @brief Draw a custom tilemap.
 * @param tilemap The map to draw.
 * @param tilemap_height The height of the map.
 * @param tilemap_width The width of the map.
 */
void Map_customDraw(Tile tilemap[MAP_MAX_SIZE][MAP_MAX_SIZE], unsigned tilemap_height, unsigned tilemap_width);

/**
 * @brief Convert from world to map tile coordinates
 * @param[out] tx Where to store tile x coord
 * @param[out] ty Where to store tile y coord
 * @param      wx World x coord
 * @param      wy World y coord
 */
void Map_worldPosToTilePos(unsigned *tx, unsigned *ty, float wx, float wy);

/**
 * @brief Convert from map tile to world coordinates
 * @param[out] wx Where to store world x coord
 * @param[out] wy Where to store world y coord
 * @param      tx Tile x coord
 * @param      ty Tile y coord
 */
void Map_tilePosToWorldPos(float *wx, float *wy, unsigned tx, unsigned ty);

/**
 * @brief Get a tile from the map
 * @param x X tile position
 * @param y Y tile position
 * @return Tile at given position
 */
Tile *Map_getTile(unsigned x, unsigned y);

/**
 * @brief Get the start tile
 * @return Start tile
 */
Tile *Map_getStartTile();

/**
 * @brief Get next tile in path
 * @param tile Current tile
 * @return Next tile
 */
Tile *Map_getNextTile(Tile *tile);

/**
 * @brief Get previous tile in path
 * @param tile Current tile
 * @return Previous tile
 */
Tile *Map_getPrevTile(Tile *tile);

/**
 * @brief Get map width
 * @return Map width
 */
unsigned Map_getWidth();

/**
 * @brief Get map height
 * @return Map height
 */
unsigned Map_getHeight();

/**
 * @brief Get map start tile x
 * @return Map start tile x
 */
unsigned Map_getStartX();

/**
 * @brief Get map start tile y
 * @return Map start tile y
 */
unsigned Map_getStartY();
