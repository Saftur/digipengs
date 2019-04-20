/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Powerup_Blind.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Powerup_Blind powerup
 */

#include "stdafx.h"

#include "Powerup_Blind.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Pedestal.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "BlindObject.h"

#define TEXTURE TEXTURES.powerup_blind
#define ASP_RAT 0.984504132f
#define SCL 32

typedef struct
{
	Object *parent;
	float alpha;
	float rotation;
} PowerupBlindData;

void Powerup_Blind_onDraw(Object *obj, PowerupBlindData *data)
{
	ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURE, Object_getPos(obj), SCL * ASP_RAT, SCL, data->rotation, data->alpha);
}

void Powerup_Blind_update(Object* obj, PowerupBlindData *data, float dt)
{
	UNREFERENCED_PARAMETER(obj);
	data->rotation -= dt;
}
void Powerup_Blind_onCollision(Collider *self, Collider *other)
{
	if (strcmp(Object_getName(other->gameObject), "Player"))
		return;
	Pedestal_resetPowerup(((PowerupBlindData *)Object_getData(self->gameObject))->parent);
	ObjectManager_addObj(BlindObject_new(((PlayerData*)Object_getData(other->gameObject))->playerNum));
	ObjectManager_delObj(self->gameObject);
}

Object *Powerup_Blind_new(AEVec2 pos, Object *parent)
{
	PowerupBlindData *data = malloc(sizeof(PowerupBlindData));

	data->parent = parent;
	data->alpha = 1.f;
	data->rotation = 0.f;

	Object *power = Object_new(NULL, Powerup_Blind_update, Powerup_Blind_onDraw, data, free, "Powerup_Blind");
	CollisionHandler_Create_Circle_Collider(power, SCL / 2, 0, Powerup_Blind_onCollision);
	Object_setPos(power, pos);

	return power;
}
