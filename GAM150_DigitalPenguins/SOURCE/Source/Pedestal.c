/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Pedestal.c
 * @author Connor Meyers
 * @brief
 */

#include "stdafx.h"

#include "Pedestal.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Powerup_Blind.h"
#include "Utils.h"
#include "Powerup_Speed.h"
#include "Powerup_Phase.h"

#define TEXTURE TEXTURES.powerup_pedastal

#define ASP_RAT 1.01042535f

#define SCL 48

#define REFRESH_TIME 3.f

#define ROTATION_SPEED 2.f

typedef enum { pNONE, pBLIND, pSPEED, pPHASE, pCOUNT }POWER;

typedef struct 
{
	POWER powerup;
	float timer;
	float rotation;
} PedestalData;

void Pedestal_onDraw(Object *obj, PedestalData *data)
{
	ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURE, Object_getPos(obj), SCL * ASP_RAT, SCL, data->rotation, 1.f);
}

void Pedestal_update(Object* obj, PedestalData *data, float dt)
{
	data->rotation += dt * ROTATION_SPEED;

	if (data->powerup == pNONE)
	{
		if (data->timer <= 0.f)
		{
			data->powerup = randrange(pNONE + 1, pCOUNT - 1);
			switch (data->powerup)
			{
			case pBLIND:
				ObjectManager_addObj(Powerup_Blind_new(Object_getPos(obj), obj));
				break;
			case pSPEED:
				ObjectManager_addObj(Powerup_Speed_new(Object_getPos(obj), obj));
				break;
			case pPHASE:
				ObjectManager_addObj(Powerup_Phase_new(Object_getPos(obj), obj));
				break;
			}
		}
		else
			data->timer -= dt;
	}
}

void Pedestal_resetPowerup(Object *pedestal)
{
	PedestalData* data = (PedestalData*)Object_getData(pedestal);
	data->powerup = pNONE;
	data->timer = REFRESH_TIME;
}

Object *Pedestal_new(AEVec2 pos)
{
	PedestalData *data = malloc(sizeof(PedestalData));

	data->timer = 0.f;
	data->powerup = pNONE;
	data->rotation = 0.f;

	Object *pedestal = Object_new(NULL, Pedestal_update, Pedestal_onDraw, data, free, "Pedestal");
	Object_setPos(pedestal, pos);

	return pedestal;
}
