#pragma once

#include <AEEngine.h>
#include "Object.h"

#define MAX_LAP_STRING_SIZE 20
#define MAX_FORMAT_STRING_SIZE 10

typedef struct LapCounter LapCounter;

Object* LapCounter_new(char* format, AEGfxTexture* font, AEVec2 textPos, AEVec2 charScale, int* currentLap);