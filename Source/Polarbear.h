/**
 * @file Polarbear.h
 * @author Connor Meyers
 * @brief Object Header for the Polarbear obstacle
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"
#include "Map.h"


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
 * @brief Sets the size of the polarbear
 *
 * @param value The new size
 *
 * @param polarbear The polarbear to set the size of
 */
void Polarbear_setSize(Object * polarbear, float value);

/**
 * @brief Gets the size of the polarbear
 *
 * @param polarbear The polarbear to get the size of
 *
 * @return The size
 */
float Polarbear_getSize(Object * polarbear);

/**
 * @brief Create new polarbear
 * @param pos Position to create polarbear at
 * @return New polarbear
 */
Object *Polarbear_new(AEVec2 pos);
