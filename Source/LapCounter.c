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
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(dt);
}

static void LapCounter_updateString(LapCounter* data)
{
	sprintf_s(data->lapAsString, MAX_LAP_STRING_SIZE, data->format, (int) *(data->lap));
}

static void LapCounter_onDraw(Object *obj, LapCounter *data)
{
	// Nothing to draw except text, which is drawn by the text object
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
    if (Camera_getCurrNum() == data->camNum)
        Object_draw(data->textObj);
}

static void LapCounter_onShutdown(LapCounter *data) {
    Object_delete(data->textObj);
    free(data);
}

Object* LapCounter_new(unsigned camNum, char* format, AEGfxTexture* font, AEVec2 textPos, AEVec2 charScale, float* currentLap)
{
	LapCounter* counterData = malloc(sizeof(LapCounter));
    counterData->camNum = camNum;
	counterData->lap = currentLap;
	counterData->format = format;

    counterData->textObj = Text_new(counterData->lapAsString, font, textPos, charScale.x, charScale.y, (Color) { 0.75f, 0, 0, 1 });

	Object *timerObj = Object_new(LapCounter_onInit, LapCounter_onUpdate, LapCounter_onDraw, counterData, LapCounter_onShutdown, "Lap Counter");
	Object_setPos(timerObj, textPos);
	return timerObj;
}