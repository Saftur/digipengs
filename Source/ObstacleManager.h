/**
 * @file ObstacleManager.h
 * @author Brand Knutson
 * @date 2/25/2019
 * @brief Load obstacles onto the map.
 */

#pragma once
#include "AEVec2.h"

typedef enum ObstacleType { 
    None = 0,
    Boulder,
    Polarbear,
    Pedestal,
    Ice
} ObstacleType;

typedef struct Obstacle {
    ObstacleType type;
    float radius;
    float rotation;
    AEVec2 pos;
} Obstacle;

/**
 * @brief Load obstacles into the current level.
 */
void ObstacleManager_loadObstacles();