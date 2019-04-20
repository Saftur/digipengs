/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Timer.h
 * @author Parker Friedland
 * @date 3/7/2019
 * @brief Timer
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"

#define MAX_TIME_STRING_SIZE 10
#define MAX_MINUTE_DIGITS 6

typedef struct Timer {
	unsigned camNum;
	Object* textObj;
	char timeAsString[MAX_TIME_STRING_SIZE];
	int decimalMinutes[MAX_MINUTE_DIGITS];
	float time;
	int intTime;
	int paused;
} Timer;

Object* Timer_new(unsigned camNum, AEGfxTexture* font, AEVec2 textPos, AEVec2 charScale, float initialTime);

void Timer_Reset(Timer *data, float newTime);

void Timer_Start(Timer* data);

void Timer_Stop(Timer* data);