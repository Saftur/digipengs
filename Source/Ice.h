/**
 * @file Ice.h
 * @author Connor Meyers
 * @brief Object Header for the Ice obstacle
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"
#include "Map.h"

#define ICE_DEFAULT_SIZE LANE_WIDTH
#define ICE_INCREMENT    (ICE_DEFAULT_SIZE / 4)
#define ICE_DECREMENT    (ICE_DEFAULT_SIZE / 8)

 /**
  * @brief Increments the size of the ice
  *
  * @param ice The ice to increase the size of
  */
void Ice_incrementSize(Object* ice);

/**
 * @brief Decrements the size of the ice
 *
 * @param boulder The ice to decrement the size of
 */
void Ice_decrementSize(Object* ice);

/**
 * @brief Create new boulder
 * @param pos Position to create ice at
 * @return New ice
 */
Object *Ice_new(AEVec2 pos);
