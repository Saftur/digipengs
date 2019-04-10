/**
 * @file Powerup_Blind.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Powerup_Blind powerup
 */

#include "stdafx.h"

#include "BlindObject.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Player.h"
#include "Utils.h"
#include "Camera.h"

#define TEXTURE TEXTURES.blindObject
#define DURATION 2.f

typedef struct
{
	float timer;
	float alpha;
	unsigned camNum;
} BlindObjectData;

void BlindObject_onDraw(Object *obj, BlindObjectData *data)
{
	UNREFERENCED_PARAMETER(obj);
	if (Camera_getCurrNum() != data->camNum) {
		AEVec2 pos;
		AEVec2Set(&pos, 0, 0);
		ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), TEXTURE, pos, AEGfxGetWinMaxX(), AEGfxGetWinMaxY() * 4, 0.f, data->alpha);
	}
}

void BlindObject_update(Object* obj, BlindObjectData *data, float dt)
{
	if (data->timer > DURATION / 2)
		data->alpha += dt;
	else
		data->alpha -= dt;

	if ((data->timer -= dt) < 0.f)
		ObjectManager_delObj(obj);
}

Object *BlindObject_new(unsigned camNum)
{
	BlindObjectData *data = malloc(sizeof(BlindObjectData));

	data->timer = DURATION;
	data->alpha = 0.5f;
	data->camNum = camNum;

	Object *blindObj = Object_new(NULL, BlindObject_update, BlindObject_onDraw, data, free, "blindObj");

	return blindObj;
}
