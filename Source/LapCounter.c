/**
 * @file LapCounter.c
 * @author Parker Friedland
 * @date 1/23/2019
 * @brief LapCounter
 */

#include "stdafx.h"
#include "LapCounter.h"
#include "TextHandler.h"
#include "objectmanager.h"

typedef struct LapCounter {
	Object* textData;
	char lapAsString[MAX_LAP_STRING_SIZE];
	char* format;
	int* lap;
} LapCounter;

static void LapCounter_updateString(LapCounter* data);

static void LapCounter_onInit(Object* obj, LapCounter *data)
{
	printf("LapCounter init\n");
	LapCounter_updateString(data);
	UNREFERENCED_PARAMETER(obj);
}

static void LapCounter_onUpdate(Object* obj, LapCounter* data, float dt)
{
	printf("LapCounter update\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(dt);
}

static void LapCounter_updateString(LapCounter* data)
{
	sprintf_s(data->lapAsString, MAX_LAP_STRING_SIZE, data->format, *(data->lap));
}

static void LapCounter_onDraw(Object *obj, LapCounter *data)
{
	// Nothing to draw except text, which is drawn by the text object
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

Object* LapCounter_new(char* format, AEGfxTexture* font, AEVec2 textPos, AEVec2 charScale, int* currentLap)
{
	LapCounter* counterData = malloc(sizeof(LapCounter));
	counterData->lap = currentLap;
	counterData->format = format;

	counterData->textData = Text_new(counterData->lapAsString, font, textPos, charScale.x, charScale.y);

	Object *timerObj = Object_new(LapCounter_onInit, LapCounter_onUpdate, LapCounter_onDraw, counterData, free, "Lap Counter");
	Object_setPos(timerObj, textPos);
	return timerObj;
}