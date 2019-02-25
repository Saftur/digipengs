/**
 * @file Polarbear.h
 * @author Connor Meyers
 * @brief Object Header for the Polarbear obstacle
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"
#include "Map.h"

#define POLARBEAR_DEFAULT_SIZE LANE_WIDTH
#define POLARBEAR_INCREMENT    (POLARBEAR_DEFAULT_SIZE / 4)
#define POLARBEAR_DECREMENT    (POLARBEAR_DEFAULT_SIZE / 8)

#define POLARBEAR_SPEED_MIN                1.0f
#define POLARBEAR_SPEED_MAX                1.5f
#define POLARBEAR_RANGE_SQUARED_MIN        60.0f
#define POLARBEAR_RANGE_SQUARED_MAX        80.0f
#define POLARBEAR_MAX_DISTANCE_SQUARED_MIN 40.0f
#define POLARBEAR_MAX_DISTANCE_SQUARED_MAX 60.0f

#define POLARBEAR_ROTATION_SPEED(size) (POLARBEAR_DEFAULT_SIZE / size)

 /**
  * @brief Increments the size of the polarbear
  *
  * @param ice The polarbear to increase the size of
  */
void Polarbear_incrementSize(Object* polarbear);

/**
 * @brief Decrements the size of the polarbear
 *
 * @param boulder The polarbear to decrement the size of
 */
void Polarbear_decrementSize(Object* polarbear);

/**
 * @brief Create new polarbear
 * @param pos Position to create polarbear at
 * @return New polarbear
 */
Object *Polarbear_new(AEVec2 pos);
