/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Powerup_Phase.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Powerup_Phase powerup
 */

#include "stdafx.h"

#include "Powerup_Phase.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Pedestal.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "BlindObject.h"

#define TEXTURE TEXTURES.powerup_phase
#define ASP_RAT 0.984504132f
#define SCL 32
#define DURATION 5.f

typedef struct
{
	Object *parent;
	float alpha;
	float rotation;
} PowerupPhaseData;


void Powerup_Phase_onDraw(Object *obj, PowerupPhaseData *data)
{
	ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURE, Object_getPos(obj), SCL * ASP_RAT, SCL, data->rotation, data->alpha);
}

void Powerup_Phase_update(Object* obj, PowerupPhaseData *data, float dt)
{
	UNREFERENCED_PARAMETER(obj);
	data->rotation -= dt;
}

void Powerup_Phase_onCollision(Collider *self, Collider *other)
{
	if (strcmp(Object_getName(other->gameObject), "Player"))
		return;
	Pedestal_resetPowerup(((PowerupPhaseData *)Object_getData(self->gameObject))->parent);

	CollisionHandler_SetPhaseDuration(other->gameObject, DURATION);

	ObjectManager_delObj(self->gameObject);
}

Object *Powerup_Phase_new(AEVec2 pos, Object *parent)
{
	PowerupPhaseData *data = malloc(sizeof(PowerupPhaseData));

	data->parent = parent;
	data->alpha = 1.f;
	data->rotation = 0.f;

	Object *power = Object_new(NULL, Powerup_Phase_update, Powerup_Phase_onDraw, data, free, "Powerup_Phase");
	CollisionHandler_Create_Circle_Collider(power, SCL / 2, 0, Powerup_Phase_onCollision);
	Object_setPos(power, pos);

	return power;
}
