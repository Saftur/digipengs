/**
 * @file FinalLap.c
 * @author Connor Meyers
 * @brief
 */

#include "stdafx.h"

#include "MapSavedText.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"

#define FLASP_RAT 4.62827225f
#define FLTEXTURE TEXTURES.text_mapsaved
#define FLSCL 128
#define POS_X 0
#define POS_Y -400

typedef struct FLData
{
	float timer;
}FLData;


void MapSavedText_update(Object* obj, FLData *data, float dt) {
	data->timer -= dt;
	if (data->timer <= 0)
		ObjectManager_delObj(obj);
}
void MapSavedText_draw(Object* obj, FLData *data) {

	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
	AEVec2 pos;
	AEVec2Set(&pos, POS_X, POS_Y);
	ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), FLTEXTURE, pos, FLSCL * FLASP_RAT, FLSCL, 0, 1.0f);
}

void MapSavedText_display()
{
	FLData *data = malloc(sizeof(FLData));
	data->timer = 1.f;
	ObjectManager_addObj(Object_new(NULL, MapSavedText_update, MapSavedText_draw, data, free, "MapSavedText"));
}