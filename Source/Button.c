/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Button.c
 * @author Parker Friedland
 * @brief Button implementation
 */
#include "stdafx.h"
#include "Button.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include <AEEngine.h>
#include "ImageHandler.h"
#include "Camera.h"

typedef struct Button {
	AEGfxTexture *defaultTexture;
	AEGfxTexture *mouseHoverTexture;
	AEGfxTexture *onClickTexture;
	float minWidth;
	float minHeight;
	float maxWidth;
	float maxHeight;
	float currentWidth;
	float currentHeight;
	float widthGrowRate;
	float heightGrowRate;
	float widthShrinkRate;
	float heightShrinkRate;
	int texture;
	unsigned camNum;
	ButtonEffectFunc buttonEffect;
} Button;

/**
 * @brief Button init function
 */
void Button_onInit(Object *obj, void *data) {
	printf("Button init\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

/**
 * @brief Button update function
 */
void Button_onUpdate(Object *obj, Button *data, float dt) {
	printf("Button update\n");
	UNREFERENCED_PARAMETER(dt);
	
	f32 objX, objY;
	AEVec2 pos = Object_getPos(obj);
	objX = pos.x;
	objY = pos.y;

	f32 objWidth, objHeight;
	objWidth = data->currentWidth;
	objHeight = data->currentHeight;

	s32 screenX, screenY;
	AEInputGetCursorPosition(&screenX, &screenY);

	//Convert mouse screen position to world position.
	float mouseX;
	float mouseY;
	Camera_ScreenCoordToCamCoord((float)screenX, (float)screenY, &mouseX, &mouseY, data->camNum);

	if (objX - objWidth / 2 < mouseX && mouseX < objX + objWidth / 2 
		&& objY - objHeight / 2 < mouseY && mouseY < objY + objHeight / 2)
	{
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
			data->texture = ON_CLICK;

			data->buttonEffect();
		}
		else
		{
			data->texture = HOVER;
		}
	}
	else if(!AEInputCheckCurr(VK_LBUTTON))
	{
		data->texture = DEFAULT;
	}

	if (data->texture == DEFAULT)
	{
		data->currentWidth -= data->widthGrowRate * dt;
		data->currentHeight -= data->heightGrowRate * dt;

		if (data->currentWidth < data->minWidth)
		{
			data->currentWidth = data->minWidth;
		}

		if (data->currentHeight < data->minHeight)
		{
			data->currentHeight = data->minHeight;
		}
	}
	else
	{
		data->currentWidth += data->widthGrowRate * dt;
		data->currentHeight += data->heightGrowRate * dt;

		if (data->currentWidth > data->maxWidth)
		{
			data->currentWidth = data->maxWidth;
		}

		if (data->currentHeight > data->maxHeight)
		{
			data->currentHeight = data->maxHeight;
		}
	}
}

void Button_onDraw(Object *obj, Button *data) 
{
	if (data->camNum == Camera_getCurrNum())
	{
		if (data->texture == DEFAULT)
		{
			ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), data->defaultTexture, 
				Object_getPos(obj), data->currentWidth, data->currentHeight, 0, 1);
		}
		else if (data->texture == HOVER)
		{
			ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), data->mouseHoverTexture, 
				Object_getPos(obj), data->currentWidth, data->currentHeight, 0, 1);
		}
		else if (data->texture == ON_CLICK)
		{
			ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), data->onClickTexture, 
				Object_getPos(obj), data->currentWidth, data->currentHeight, 0, 1);
		}
	}
}

Object *Button_new(ButtonEffectFunc buttonEffect, 
		AEGfxTexture *defaultTexture, AEGfxTexture *mouseHoverTexture, AEGfxTexture *onClickTexture, 
		float x, float y, float minWidth, float minHeight, float maxWidth, float maxHeight, 
		float growTime, float shrinkTime, unsigned camNum) 
{
	Button *buttonData = malloc(sizeof(Button));
	buttonData->buttonEffect = buttonEffect;
	buttonData->defaultTexture = defaultTexture;
	buttonData->mouseHoverTexture = mouseHoverTexture;
	buttonData->onClickTexture = onClickTexture;
	buttonData->camNum = camNum;
	buttonData->minWidth = minWidth;
	buttonData->minHeight = minHeight;
	buttonData->maxWidth = maxWidth;
	buttonData->maxHeight = maxHeight;
	buttonData->currentWidth = minWidth;
	buttonData->currentHeight = minHeight;
	buttonData->widthGrowRate = growTime * (maxWidth - minWidth);
	buttonData->heightGrowRate = growTime * (maxHeight - minHeight);
	buttonData->widthShrinkRate = shrinkTime * (maxWidth - minWidth);
	buttonData->heightShrinkRate = shrinkTime * (maxHeight - minHeight);

	Object *buttonObj = Object_new(Button_onInit, Button_onUpdate, Button_onDraw, buttonData, free, "Button");
	AEVec2 pos;
	pos.x = x;
	pos.y = y;
	Object_setPos(buttonObj, pos);
	return buttonObj;
}
