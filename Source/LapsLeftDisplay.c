/**
 * @file LapsLeftDisplay.c
 * @author Connor Meyers
 * @brief
 */

#include "stdafx.h"

#include "LapsLeftDisplay.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"

#define ASP_RAT 3.07617188f
#define TEXTURE_ONE TEXTURES.text_lapleft1
#define TEXTURE_TWO TEXTURES.text_lapleft2
#define SCL 256
#define POS_X 0
#define POS_Y 200

typedef struct Data
{
	float timer;
	unsigned camNum;
	unsigned lapNum;
	float alpha;
}Data;


void LapsLeftDisplay_update(Object* obj, Data *data, float dt) {
	data->timer -= dt;
	if (data->timer <= 0)
		ObjectManager_delObj(obj);
	if (data->timer < 1.f)
		data->alpha -= dt;
}

void LapsLeftDisplay_draw(Object* obj, Data *data) {

	UNREFERENCED_PARAMETER(obj);
	if (Camera_getCurrNum() == data->camNum) {
		AEVec2 pos;
		AEVec2Set(&pos, POS_X, POS_Y);
		AEGfxTexture *texture;
		if (data->lapNum == 1)
			texture = TEXTURE_ONE;
		else
			texture = TEXTURE_TWO;
		ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), texture, pos, SCL * ASP_RAT, SCL, 0, data->alpha);
	}
}

void LapsLeftDisplay_display(unsigned camNum, unsigned lapNum)
{
	Data *data = malloc(sizeof(Data));
	data->timer = 2.f;
	data->camNum = camNum;
	data->lapNum = lapNum;
	data->alpha = 1.f;
	ObjectManager_addObj(Object_new(NULL, LapsLeftDisplay_update, LapsLeftDisplay_draw, data, free, "LapsLeftDisplay"));
}