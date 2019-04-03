/**
 * @file FinalLap.c
 * @author Connor Meyers
 * @brief
 */

#include "stdafx.h"

#include "FinalLap.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"

#define FLASP_RAT 3.80104712f
#define FLTEXTURE TEXTURES.text_fl
#define FLSCL 192
#define POS_X 0
#define POS_Y 200

typedef struct FLData
{
	float timer;
	unsigned camNum;
}FLData;


void FinalLap_update(Object* obj, FLData *data, float dt) {
	data->timer -= dt;
	if (data->timer <= 0)
		ObjectManager_delObj(obj);
}
void FinalLap_draw(Object* obj, FLData *data) {

	UNREFERENCED_PARAMETER(obj);
	if (Camera_getCurrNum() == data->camNum) {
		AEVec2 pos;
		AEVec2Set(&pos, POS_X, POS_Y);
		ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), FLTEXTURE, pos, FLSCL * FLASP_RAT, FLSCL, 0, 1.0f);
	}
}

void FinalLap_display(unsigned camNum)
{
	FLData *data = malloc(sizeof(FLData));
	data->timer = 1.5f;
	data->camNum = camNum;
	ObjectManager_addObj(Object_new(NULL, FinalLap_update, FinalLap_draw, data, free, "FinalLap"));
}