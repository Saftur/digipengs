/**
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
	objWidth = data->width;
	objHeight = data->height;

	s32 screenX, screenY;
	AEInputGetCursorPosition(&screenX, &screenY);

	//Convert mouse screen position to world position.
	float mouseX;
	float mouseY;
	AEGfxConvertScreenCoordinatesToWorld((float)screenX, (float)screenY, &mouseX, &mouseY);

	if (objX - objWidth / 2 < mouseX && mouseX < objX + objWidth / 2 && objY - objHeight / 2 < mouseY && mouseY < objY + objHeight / 2)
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
	else
	{
		data->texture = DEFAULT;
	}
}

void Button_onDraw(Object *obj, Button *data) {
    
	if (data->texture == DEFAULT)
	{
		ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->defaultTexture, Object_getPos(obj), data->width, data->height, 0, 1);
	}
	else if (data->texture == HOVER)
	{
        ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->mouseHoverTexture, Object_getPos(obj), data->width, data->height, 0, 1);
	}
	else if (data->texture == ON_CLICK)
	{
        ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->onClickTexture, Object_getPos(obj), data->width, data->height, 0, 1);
	}
}

Object *Button_new(ButtonEffectFunc buttonEffect, AEGfxTexture *defaultTexture, AEGfxTexture *mouseHoverTexture, AEGfxTexture *onClickTexture, 
				   float x, float y, float width, float height) {
	Button *buttonData = malloc(sizeof(Button));
	buttonData->buttonEffect = buttonEffect;
	buttonData->defaultTexture = defaultTexture;
	buttonData->mouseHoverTexture = mouseHoverTexture;
	buttonData->onClickTexture = onClickTexture;
	Object *buttonObj = Object_new(Button_onInit, Button_onUpdate, Button_onDraw, buttonData, free, "Button");
	AEVec2 pos;
	pos.x = x;
	pos.y = y;
	Object_setPos(buttonObj, pos);
	buttonData->width = width;
	buttonData->height = height;
	return buttonObj;
}
