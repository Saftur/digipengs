/**
 * @file Map.h
 * @author Arthur Bouvier
 * @date 2/5/2019
 * @brief Map interface
 */
#pragma once

#define LANE_WIDTH 64

#define MAP_MAX_SIZE 8

#define TILE_SIZE 320

/**
 * @brief A side of a tile
 */
typedef enum {
    SLeft, SRight, SUp, SDown
} Side;

/**
 * @brief A Tile
 */
typedef struct Tile {
    Side from; ///< Side path comes from
    Side to;   ///< Side path goes to
} Tile;

/**
 * @brief Initialize map
 * @param filename Name of map file
 */
void Map_init(const char *filename);

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
Tile Map_getTile(unsigned x, unsigned y);

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
