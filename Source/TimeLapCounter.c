/**
 * @file Level1.c
 * @author Parker Friedland
 * @date 1/23/2019
 * @brief TitleScreen
 */

#include "stdafx.h"
#include "TimeLapCounter.h"
#include "TextHandler.h"
#include "objectmanager.h"

typedef struct Timer {
	Object* textData;
	char timeAsString[MAX_TIME_STRING_SIZE];
	int decimalMinutes[MAX_MINUTE_DIGITS];
	float time;
	int intTime;
} Timer;

static void Timer_updateString(Timer* data);

void Timer_Reset(Timer *data, float newTime)
{
	data->time = newTime;
}

static void Timer_onInit(Object *obj, Timer *data)
{
	printf("Timer init\n");
	Timer_updateString(data);
	UNREFERENCED_PARAMETER(obj);
}

static void Timer_onUpdate(Object* obj, Timer* data, float dt)
{
	printf("Timer update\n");

	data->time += dt;
	int currentIntTime = (int) data->time;

	if (currentIntTime != data->intTime)
	{
		data->intTime = currentIntTime;

		Timer_updateString(data);
	}
	UNREFERENCED_PARAMETER(obj);
}

static void Timer_updateString(Timer* data)
{
	int currentMinutes = data->intTime / 60;
	int currentSeconds = data->intTime % 60;

	int decimalIndex = MAX_MINUTE_DIGITS - 1;
	int stringIndex = 0;
	for (decimalIndex = 0; decimalIndex < MAX_MINUTE_DIGITS && currentMinutes > 0; decimalIndex++)
	{
		data->decimalMinutes[decimalIndex] = currentMinutes % 10;
		currentMinutes /= 10;
	}

	for (stringIndex = 0; decimalIndex > 0; stringIndex++)
	{
		data->timeAsString[stringIndex] = ((char)data->decimalMinutes[--decimalIndex]) + '0';
	}
	data->timeAsString[stringIndex++] = ':';
	data->timeAsString[stringIndex++] = ((char) (currentSeconds / 10)) + '0';
	data->timeAsString[stringIndex++] = ((char) (currentSeconds % 10)) + '0';
	data->timeAsString[stringIndex] = '\0';
}

static void Timer_onDraw(Object *obj, Timer *data)
{
	// Nothing to draw except text, which is drawn by the text object
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

Object* Timer_new(AEGfxTexture* font, AEVec2 textPos, AEVec2 charScale, float initialTime)
{
	Timer* timerData = malloc(sizeof(Timer));
	timerData->time = initialTime;
	timerData->intTime = (int) initialTime;
	timerData->textData = Text_new(timerData->timeAsString, font, textPos, charScale.x, charScale.y);

	Object *timerObj = Object_new(Timer_onInit, Timer_onUpdate, Timer_onDraw, timerData, free, "Timer");
	Object_setPos(timerObj, textPos);
	return timerObj;
}