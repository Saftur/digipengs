/**
 * @file ObstacleManager.c
 * @author Brand Knutson
 * @date 2/5/2019
 * @brief Create and manage obstacles.
 */

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include "ObstacleManager.h"
#include "Map.h"
#include "Boulder.h"
#include "objectmanager.h"

#define MAX_OBSTACLES_PER_TILE 1

int randomInt(int lower, int upper);

void ObstacleManager_generateObstacles(AEVec2 startPos)
{
    srand((int)time(NULL));
    AEVec2 tileWorldPos;
    unsigned tileX, tileY;

    Map_worldPosToTilePos(&tileX, &tileY, startPos.x, startPos.y);

    unsigned initialTileX = tileX, initialTileY = tileY;

    do {
        Map_tilePosToWorldPos(&tileWorldPos.x, &tileWorldPos.y, tileX, tileY);
        Tile tile = Map_getTile(tileX, tileY);
        int numObstacles = randomInt(0, MAX_OBSTACLES_PER_TILE);

        //If the tile is a straight segment.
        if (tile.from == SDown && tile.to == SUp || tile.from == SUp && tile.to == SDown 
        || tile.from == SLeft && tile.to == SRight || tile.from == SRight && tile.to == SLeft) {
            for (int i = 0; i < numObstacles; i++) {
                //Get the position to create the obstacle at.
                int lane = randomInt(0, 4);
                AEVec2 obstaclesPos;
                
                if (tile.to == SRight || tile.to == SLeft) {
                    obstaclesPos.y = tileWorldPos.y + (LANE_WIDTH * 2) - (LANE_WIDTH * lane);
                    obstaclesPos.x = tileWorldPos.x - (TILE_SIZE / 2) + randomInt(0, TILE_SIZE);
                }
                else {
                    obstaclesPos.x = tileWorldPos.x + (LANE_WIDTH * 2) - (LANE_WIDTH * lane);
                    obstaclesPos.y = tileWorldPos.y - (TILE_SIZE / 2) + randomInt(0, TILE_SIZE);
                }

                //Get the type of boulder to create.
                BoulderInfo *boulderType = NULL;
                switch (randomInt(1, 4)) {
                case 1:
                    boulderType = BOULDER_TYPES.tiny;
                    break;
                case 2:
                    boulderType = BOULDER_TYPES.normal;
                    break;
                case 3:
                    boulderType = BOULDER_TYPES.big;
                    break;
                case 4:
                    boulderType = BOULDER_TYPES.giant;
                    break;
                }

                Object *boulder = Boulder_new(boulderType, obstaclesPos);
                ObjectManager_addObj(boulder);
            }
        }

        if (tile.to == SLeft) tileX--;
        else if (tile.to == SRight) tileX++;
        else if (tile.to == SDown) tileY++;
        else tileY--;
    } while (tileX!= initialTileX || tileY != initialTileY);
}

int randomInt(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}