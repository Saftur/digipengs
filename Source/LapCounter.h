/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LapCounter.h
 * @author Parker Friedland
 * @date 1/23/2019
 * @brief LapCounter
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"

#define MAX_LAP_STRING_SIZE 20
#define MAX_FORMAT_STRING_SIZE 10

typedef struct LapCounter LapCounter;

Object* LapCounter_new(unsigned camNum, char* format, AEGfxTexture* font, AEVec2 textPos, AEVec2 charScale, float* currentLap);