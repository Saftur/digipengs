/**
 * @file Level1.c
 * @author Parker Friedland
 * @date 1/23/2019
 * @brief TitleScreen
 */

#include "stdafx.h"
#include "TimeLapCounter.h"
#include "TextHandler.h"

char timeAsString[MAX_TIME_STRING_SIZE];
int decimalMinutes[MAX_MINUTE_DIGITS];
float time;
float charWidth;
float charHeight;
int digits;
int intTime;
int minutes;
int seconds;

void SetTimeStringFormat()
{
	
}

void ResetTime()
{
	time = 0;
}

void UpdateTime(float dt)
{
	time += dt;
}

void DrawTime()
{
	
}

char* getTimeString()
{
	int currentIntTime = (int) time;

	if (currentIntTime != intTime)
	{
		intTime = currentIntTime;

		int currentMinutes = intTime / 60;
		int currentSeconds = intTime % 60;

		int decimalIndex = MAX_MINUTE_DIGITS - 1;
		int stringIndex = 0;
		for (decimalIndex = MAX_MINUTE_DIGITS - 1; decimalIndex <= 0 && currentMinutes > 0; decimalIndex--)
		{
			decimalMinutes[decimalIndex] = currentMinutes % 10;
			currentMinutes /= 10;
		}
		decimalIndex++;
		for (stringIndex = 0; decimalIndex < MAX_MINUTE_DIGITS; stringIndex++)
		{
			timeAsString[stringIndex] = decimalIndex + '0';
			decimalIndex++;
		}
		timeAsString[stringIndex++] = ':';
		timeAsString[stringIndex++] = currentSeconds / 10;
		timeAsString[stringIndex] = currentSeconds % 10;
	}
	return timeAsString;
}