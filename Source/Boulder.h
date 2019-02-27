/**
 * @file Boulder.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Boulder obstacle
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"

#define BOULDER_DEFAULT_SIZE 64
#define BOULDER_INCREMENT    (BOULDER_DEFAULT_SIZE / 4)
#define BOULDER_DECREMENT    (BOULDER_DEFAULT_SIZE / 8)

/**
 * @brief Increments the size of the boulder
 *
 * @param boulder The boulder to increase the size of
 */
void Boulder_incrementSize(Object* boulder);

/**
 * @brief Decrements the size of the boulder
 *
 * @param boulder The boulder to decrement the size of
 */
void Boulder_decrementSize(Object* boulder);

/**
 * @brief Sets the size of the boulder
 *
 * @param value The new size
 *
 * @param boulder The boulder to set the size of
 */
void Boulder_setSize(Object * boulder, float value);

/**
 * @brief Gets the size of the boulder
 *
 * @param boulder The boulder to get the size of
 *
 * @return The size
 */
float Boulder_getSize(Object * boulder);

/**
 * @brief Create new boulder
 * @param pos Position to create boulder at
 * @return New boulder
 */
Object *Boulder_new(AEVec2 pos);
