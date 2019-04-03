/**
 * @file Button.c
 * @author Parker Friedland
 * @brief Button implementation
 */
#include "stdafx.h"
#include "DragButton.h"
#include "Button.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include <AEEngine.h>
#include "ImageHandler.h"

/**
 * @brief Button init function
 */
void DragButton_onInit(Object *obj, void *data) 
{
	printf("Button init\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

/**
 * @brief Button update function
 */
void DragButton_onUpdate(Object *obj, DragButton *data, float dt) {
	printf("Button update\n");
	UNREFERENCED_PARAMETER(dt);
	
	f32 button_X, button_Y, button_Width, button_Height;
	button_X = data->button_X;
	button_Y = data->button_Y;
	button_Width = data->button_Width;
	button_Height = data->button_Height;

	s32 screenX, screenY;
	AEInputGetCursorPosition(&screenX, &screenY);

	//Convert mouse screen position to world position.
	float mouseX;
	float mouseY;
	AEGfxConvertScreenCoordinatesToWorld((float)screenX, (float)screenY, &mouseX, &mouseY);

	if (button_X - button_Width/2 < mouseX && mouseX < button_X + button_Width/2 && button_Y - button_Height/2 < mouseY && mouseY < button_Y + button_Height/2)
	{
		if (AEInputCheckCurr(VK_LBUTTON))
		{
			data->texture = ON_CLICK;
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

	if (data->texture == ON_CLICK)
	{
		float locationOnTrack = ((mouseX - Object_getPos(obj).x) * cosf(data->track_Angle) + (mouseY - Object_getPos(obj).y) * cosf(data->track_Angle)) / data->track_Length;

		if (locationOnTrack < -0.5f)
		{
			locationOnTrack = -0.5f;
		}

		if (locationOnTrack > 0.5f)
		{
			locationOnTrack = 0.5f;
		}

		*(data->effectedVariable) = (data->min + data->max) / 2 + locationOnTrack * (data->max - data->min);
	}

	AEVec2 pos = Object_getPos(obj);
	data->button_X = pos.x + data->track_Length*cosf(data->track_Angle)*(*(data->effectedVariable) - ((data->min + data->max) / 2)) / (data->max - data->min);
	data->button_Y = pos.y + data->track_Length*sinf(data->track_Angle)*(*(data->effectedVariable) - ((data->min + data->max) / 2)) / (data->max - data->min);
}

void DragButton_onDraw(Object *obj, DragButton *data) 
{
	ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->track_Texture, Object_getPos(obj), 
		data->track_Length, data->track_Thickness, data->track_Angle, 1);

	AEVec2 buttonPos;
	buttonPos.x = data->button_X;
	buttonPos.y = data->button_Y;

	if (data->texture == DEFAULT)
	{
		ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->button_DefaultTexture, buttonPos, 
			data->button_Width, data->button_Height, 0, 1);
	}
	else if (data->texture == HOVER)
	{
		ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->button_MouseHoverTexture, buttonPos, 
			data->button_Width, data->button_Height, 0, 1);
	}
	else if (data->texture == ON_CLICK)
	{
		ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->button_OnClickTexture, buttonPos, 
			data->button_Width, data->button_Height, 0, 1);
	}
}

Object* DragButton_new(float* effectedVariable, float min, float max, AEGfxTexture* track_Texture, AEGfxTexture* button_DefaultTexture, 
		AEGfxTexture* button_MouseHoverTexture, AEGfxTexture* button_OnClickTexture,
		float x, float y, float track_Angle, float track_Length, float track_Thickness, float button_Width, float button_Height)
{
	DragButton *buttonData = malloc(sizeof(DragButton));
	buttonData->effectedVariable = effectedVariable;
	buttonData->min = min;
	buttonData->max = max;
	buttonData->track_Texture = track_Texture;
	buttonData->button_DefaultTexture = button_DefaultTexture;
	buttonData->button_MouseHoverTexture = button_MouseHoverTexture;
	buttonData->button_OnClickTexture = button_OnClickTexture;
	buttonData->texture = DEFAULT;
	buttonData->track_Angle = track_Angle;
	buttonData->track_Length = track_Length;
	buttonData->track_Thickness = track_Thickness;
	buttonData->button_Width = button_Width;
	buttonData->button_Height = button_Height;

	Object *buttonObj = Object_new(DragButton_onInit, DragButton_onUpdate, DragButton_onDraw, buttonData, free, "Drag Button");
	AEVec2 pos;
	pos.x = x;
	pos.y = y;
	Object_setPos(buttonObj, pos);
	return buttonObj;
}