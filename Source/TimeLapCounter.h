#pragma once

#define MAX_TIME_STRING_SIZE 10
#define MAX_MINUTE_DIGITS 6

Object* Timer_new(AEGfxTexture* font, AEVec2 textPos, AEVec2 charScale, float initialTime);

void Timer_Reset(Timer *data, float newTime);