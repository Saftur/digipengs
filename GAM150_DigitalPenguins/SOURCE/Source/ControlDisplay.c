/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file ControlDisplay.c
 * @author Connor Meyers
 * @brief
 */

#include "stdafx.h"

#include "ControlDisplay.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"

#define ASP_RAT 1.99551904f
#define TEXTURE_ONE TEXTURES.controls_p2
#define TEXTURE_TWO TEXTURES.controls_p1
#define SCL 256
#define POS_X 0
#define POS_Y -100

typedef struct Data
{
	float timer;
	unsigned camNum;
	float alpha;
}Data;


void ControlDisplay_update(Object* obj, Data *data, float dt) {
	data->timer -= dt;
	if (data->timer <= 0)
		ObjectManager_delObj(obj);
	if (data->timer < 1.f)
		data->alpha -= dt;
}

void ControlDisplay_draw(Object* obj, Data *data) {

	UNREFERENCED_PARAMETER(obj);
	if (Camera_getCurrNum() == data->camNum) {
		AEVec2 pos;
		AEVec2Set(&pos, POS_X, POS_Y);
		AEGfxTexture *texture;
		if (data->camNum == 1)
			texture = TEXTURE_ONE;
		else
			texture = TEXTURE_TWO;
		ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), texture, pos, SCL * ASP_RAT, SCL, 0, data->alpha);
	}
}

void ControlDisplay_display(unsigned camNum)
{
	Data *data = malloc(sizeof(Data));
	data->timer = 2.f;
	data->camNum = camNum;
	data->alpha = 1.f;
	ObjectManager_addObj(Object_new(NULL, ControlDisplay_update, ControlDisplay_draw, data, free, "ControlDisplay"));
}