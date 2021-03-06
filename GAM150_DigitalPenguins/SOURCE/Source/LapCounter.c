/**
 * Project: DigitalPenguins
 * All content � 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LapCounter.c
 * @author Parker Friedland
 * @date 3/7/2019
 * @brief LapCounter
 */

#include "stdafx.h"
#include "LapCounter.h"
#include "TextHandler.h"
#include "objectmanager.h"
#include "Camera.h"

typedef struct LapCounter {
    unsigned camNum;
	Object* textObj;
	char lapAsString[MAX_LAP_STRING_SIZE];
	char* format;
	float* lap;
} LapCounter;

static void LapCounter_updateString(LapCounter* data);

static void LapCounter_onInit(Object* obj, LapCounter *data)
{
	printf("LapCounter init\n");
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(obj);
}

static void LapCounter_onUpdate(Object* obj, LapCounter* data, float dt)
{
	printf("LapCounter update\n");
	LapCounter_updateString(data);
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(dt);
}

static void LapCounter_updateString(LapCounter* data)
{
	sprintf_s(data->lapAsString, MAX_LAP_STRING_SIZE, data->format, (int) *(data->lap));
}

static void LapCounter_onDraw(Object *obj, LapCounter *data)
{
	UNREFERENCED_PARAMETER(obj);
    if (Camera_getCurrNum() == data->camNum)
        Object_draw(data->textObj);
}

static void LapCounter_onShutdown(LapCounter *data) 
{
	UNREFERENCED_PARAMETER(data);
}

Object* LapCounter_new(unsigned camNum, char* format, AEGfxTexture* font, AEVec2 textPos, AEVec2 charScale, float* currentLap)
{
	LapCounter* counterData = malloc(sizeof(LapCounter));
    counterData->camNum = camNum;
	counterData->lap = currentLap;
	counterData->format = format;

    Object* textObj = Text_new(counterData->lapAsString, font, textPos, charScale.x, charScale.y, (Color) { 1, 1, 1, 1 }, camNum);
	counterData->textObj = textObj;
	ObjectManager_addObj(textObj);

	Object* counterObj = Object_new(
		LapCounter_onInit, LapCounter_onUpdate, LapCounter_onDraw, counterData, LapCounter_onShutdown, "Lap Counter");
	Object_setPos(counterObj, textPos);
	return counterObj;
}