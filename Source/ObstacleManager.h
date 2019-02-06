/**
 * @file ObstacleManager.h
 * @author Brand Knutson
 * @date 1/30/2019
 * @brief Create and manage obstacles.
 */

#pragma once

#include "AEVec2.h"

typedef enum ObstacleType { Boulder } ObstacleType;

/**
 * @brief Generate obstacles throughought the map.
 * @param startPos Where to start generating obstacles from, should probably be the player's start position.
 */
void ObstacleManager_generateObstacles(AEVec2 startPos);