/**
 * @file GameStartTimer.c
 * @author Connor Meyers
 * @brief
 */

#include "stdafx.h"

#include "GameStartTimer.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"

#define ASP_RAT 2.48214286f

#define SCL 128
#define ALPHA 0.75
#define POS_X 0
#define POS_Y 0

#define TIME_PER_STATE 1.0f

static Object *text = NULL;
typedef enum {sREADY, sSET, sGO}STAGE;
static float time;
static STAGE state;
static AEGfxTexture *textures[3];
static bool started = false;

void GameStartTimer_onDraw(Object *obj, void *data)
{
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
	AEVec2 pos;
	AEVec2Set(&pos, POS_X, POS_Y);
	ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), textures[state], pos, SCL * ASP_RAT, SCL, 0, ALPHA);
}

void GameStartTimer_free(void *data)
{
	UNREFERENCED_PARAMETER(data);
	text = NULL;
	started = true;
}

void GameStartTimer_update(Object* obj, void *data, float dt)
{
	UNREFERENCED_PARAMETER(data);
	time -= dt;
	if (time <= 0)
	{
		if (++state > sGO)
		{
			Object_delete(obj);
		}
		else
			time = TIME_PER_STATE;
	}
}

void GameStartTimer_init()
{
	if (text)return;

	if (!textures)
	{
		textures[0] = TEXTURES.text_ready;
		textures[1] = TEXTURES.text_set;
		textures[2] = TEXTURES.text_go;
	}

	AEVec2 pos;
	AEVec2Set(&pos, POS_X, POS_Y);
	time = TIME_PER_STATE;
	state = sREADY;
	started = false;
	text = Object_new(NULL, GameStartTimer_update, GameStartTimer_onDraw, NULL, GameStartTimer_free, "GameStartTimer");
	Object_setPos(text, pos);

	ObjectManager_addObj(text);
}

bool GameStartTimer_started() {
	return started;
}
