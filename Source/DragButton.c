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
#include "Camera.h"

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
	float button_minWidth;
	float button_minHeight;
	float button_maxWidth;
	float button_maxHeight;
	float button_currentWidth;
	float button_currentHeight;
	float button_widthGrowRate;
	float button_heightGrowRate;
	float button_widthShrinkRate;
	float button_heightShrinkRate;
	float button_X;
	float button_Y;
	unsigned camNum;
} DragButton;

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

	f32 button_X, button_Y, button_Width, button_Height, track_Width, track_Height;
	button_X = data->button_X;
	button_Y = data->button_Y;
	button_Width = data->button_currentWidth;
	button_Height = data->button_currentHeight;
	track_Width = 0;
	track_Height = 0;

	if (fabsf(data->track_Angle - 0) < EPSILON || fabsf(data->track_Angle - PI) < EPSILON)
	{

		track_Width = data->track_Length;
		track_Height = data->track_Thickness;
	}
	if (fabsf(data->track_Angle - PI / 2) < EPSILON || fabsf(data->track_Angle - 3 * PI / 2) < EPSILON)
	{
		track_Width = data->track_Thickness;
		track_Height = data->track_Length;
	}

	AEVec2 trackPos = Object_getPos(obj);

	s32 screenX, screenY;
	AEInputGetCursorPosition(&screenX, &screenY);

	//Convert mouse screen position to world position.
	float mouseX;
	float mouseY;
	Camera_ScreenCoordToCamCoord((float)screenX, (float)screenY, &mouseX, &mouseY, data->camNum);

	if (trackPos.x - track_Width / 2 < mouseX && mouseX < trackPos.x + track_Width / 2
		&& trackPos.y - track_Height / 2 < mouseY && mouseY < trackPos.y + track_Height / 2
		&& AEInputCheckCurr(VK_LBUTTON))
	{
		data->texture = ON_CLICK;

		data->button_currentWidth = data->button_maxWidth;
		data->button_currentHeight = data->button_maxHeight;
	}
	else if (button_X - button_Width / 2 < mouseX && mouseX < button_X + button_Width / 2
		&& button_Y - button_Height / 2 < mouseY && mouseY < button_Y + button_Height / 2)
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
	else if (!AEInputCheckCurr(VK_LBUTTON))
	{
		data->texture = DEFAULT;
	}

	if (data->texture == ON_CLICK)
	{
		float locationOnTrack = ((mouseX - Object_getPos(obj).x) * cosf(data->track_Angle)
			+ (mouseY - Object_getPos(obj).y) * cosf(data->track_Angle)) / data->track_Length;

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

	if (data->texture == DEFAULT)
	{
		data->button_currentWidth -= data->button_widthGrowRate * dt;
		data->button_currentHeight -= data->button_heightGrowRate * dt;

		if (data->button_currentWidth < data->button_minWidth)
		{
			data->button_currentWidth = data->button_minWidth;
		}

		if (data->button_currentHeight < data->button_minHeight)
		{
			data->button_currentHeight = data->button_minHeight;
		}
	}
	else
	{
		data->button_currentWidth += data->button_widthGrowRate * dt;
		data->button_currentHeight += data->button_heightGrowRate * dt;

		if (data->button_currentHeight > data->button_maxWidth)
		{
			data->button_currentHeight = data->button_maxWidth;
		}

		if (data->button_currentWidth > data->button_maxHeight)
		{
			data->button_currentWidth = data->button_maxHeight;
		}
	}

	AEVec2 pos = Object_getPos(obj);
	data->button_X = pos.x + data->track_Length*cosf(data->track_Angle)*(*(data->effectedVariable)
		- ((data->min + data->max) / 2)) / (data->max - data->min);

	data->button_Y = pos.y + data->track_Length*sinf(data->track_Angle)*(*(data->effectedVariable)
		- ((data->min + data->max) / 2)) / (data->max - data->min);
}

void DragButton_onDraw(Object *obj, DragButton *data)
{
	if (data->camNum == Camera_getCurrNum())
	{
		ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->track_Texture, Object_getPos(obj),
			data->track_Length, data->track_Thickness, data->track_Angle, 1);

		AEVec2 buttonPos;
		buttonPos.x = data->button_X;
		buttonPos.y = data->button_Y;

		if (data->texture == DEFAULT)
		{
			ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->button_DefaultTexture, buttonPos,
				data->button_currentWidth, data->button_currentHeight, 0, 1);
		}
		else if (data->texture == HOVER)
		{
			ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->button_MouseHoverTexture, buttonPos,
				data->button_currentWidth, data->button_currentHeight, 0, 1);
		}
		else if (data->texture == ON_CLICK)
		{
			ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->button_OnClickTexture, buttonPos,
				data->button_currentWidth, data->button_currentHeight, 0, 1);
		}
	}
}

Object* DragButton_new(float* effectedVariable, float min, float max, AEGfxTexture* track_Texture, AEGfxTexture* button_DefaultTexture,
	AEGfxTexture* button_MouseHoverTexture, AEGfxTexture* button_OnClickTexture,
	float x, float y, float track_Angle, float track_Length, float track_Thickness,
	float button_minWidth, float button_minHeight, float button_maxWidth, float button_maxHeight,
	float growTime, float shrinkTime, unsigned camNum)
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
	buttonData->button_minWidth = button_minWidth;
	buttonData->button_minHeight = button_minHeight;
	buttonData->button_maxWidth = button_maxWidth;
	buttonData->button_maxHeight = button_maxHeight;
	buttonData->button_currentWidth = button_minWidth;
	buttonData->button_currentHeight = button_minHeight;
	buttonData->button_widthGrowRate = growTime * (button_maxWidth - button_minWidth);
	buttonData->button_heightGrowRate = growTime * (button_maxHeight - button_minHeight);
	buttonData->button_widthShrinkRate = shrinkTime * (button_maxWidth - button_minWidth);
	buttonData->button_heightShrinkRate = shrinkTime * (button_maxHeight - button_minHeight);
	buttonData->camNum = camNum;

	Object *buttonObj = Object_new(DragButton_onInit, DragButton_onUpdate, DragButton_onDraw, buttonData, free, "Drag Button");
	AEVec2 pos;
	pos.x = x;
	pos.y = y;
	Object_setPos(buttonObj, pos);
	return buttonObj;
}