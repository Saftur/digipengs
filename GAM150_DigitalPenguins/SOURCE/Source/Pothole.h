/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Pothole.h
 * @author Connor Meyers
 * @brief Object Header for the Pothole obstacle
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"
#include "Map.h"

#define POTHOLE_DEFAULT_SIZE LANE_WIDTH
#define POTHOLE_INCREMENT    (POTHOLE_DEFAULT_SIZE / 4)
#define POTHOLE_DECREMENT    (POTHOLE_DEFAULT_SIZE / 8)

 /**
  * @brief Increments the size of the pothole
  *
  * @param ice The pothole to increase the size of
  */
void Pothole_incrementSize(Object* pothole);

/**
 * @brief Decrements the size of the pothole
 *
 * @param boulder The pothole to decrement the size of
 */
void Pothole_decrementSize(Object* pothole);

/**
 * @brief Sets the size of the pothole
 *
 * @param value The new size
 *
 * @param pothole The pothole to set the size of
 */
void Pothole_setSize(Object * pothole, float value);

/**
 * @brief Gets the size of the pothole
 *
 * @param pothole The pothole to get the size of
 *
 * @return The size
 */
float Pothole_getSize(Object * pothole);


/**
 * @brief Create new pothole
 * @param pos Position to create pothole at
 * @return New pothole
 */
Object *Pothole_new(AEVec2 pos);
