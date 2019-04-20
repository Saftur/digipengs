/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Background.h
 * @author Connor Meyers
 * @brief Object Header for the background
 */

#pragma once

#include <AEEngine.h>
#include "ImageHandler.h"
#include "object.h"

/**
 * @brief Create new background
 * @return New background
 */
Object *Background_create();

/**
 * @brief Draw the background
 */
void Background_onDraw();