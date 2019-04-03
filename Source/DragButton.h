/**
 * @file Button.h
 * @author Parker Friedland
 * @brief Example Game Object
 */
#pragma once

#include "Object.h"

#define DEFAULT 0
#define HOVER 1
#define ON_CLICK 2

typedef struct DragButton {
	float* effectedVariable;
	float min;
	float max;
	AEGfxTexture* track_Texture;
	AEGfxTexture* button_DefaultTexture;
	AEGfxTexture* button_MouseHoverTexture;
	AEGfxTexture* button_OnClickTexture;
	int texture;
	float track_Angle;
	float track_Length;
	float track_Thickness;
	float button_Width;
	float button_Height;
	float button_X;
	float button_Y;
} DragButton;

/**
 * @brief Create new Button
 * @return New Button
 */
Object *DragButton_new(float* effectedVariable, float min, float max, AEGfxTexture *track_Texture, AEGfxTexture *button_DefaultTexture,
	AEGfxTexture *button_MouseHoverTexture, AEGfxTexture *button_OnClickTexture,
	float x, float y, float track_Angle, float track_Length, float track_Thickness, float button_Width, float button_Height);