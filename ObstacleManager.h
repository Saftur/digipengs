/**
 * @file ObstacleManager.h
 * @author Brand Knutson
 * @date 1/30/2019
 * @brief Create and manage obstacles.
 */

#pragma once

typedef enum ObstacleType { Boulder } ObstacleType;

/**
 * @brief Create a new obstacle.
 * @param type The type of obstacle to create.
 */
void ObstacleManager_Create_Obstacle(ObstacleType type);