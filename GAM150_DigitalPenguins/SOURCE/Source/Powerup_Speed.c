/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Powerup_Speed.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Pedastal powerup
 */

#include "stdafx.h"

#include "Powerup_Speed.h"
#include "objectmanager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Pedestal.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "BlindObject.h"

#define TEXTURE TEXTURES.powerup_speed
#define ASP_RAT 0.984504132f
#define SCL 32
#define DURATION 2.f
#define SPEED_BONUS 1.4f

typedef struct
{
	Object *parent;
	float alpha;
	float rotation;
} PowerupSpeedData;

static void BoostPlayer(Object *player);

void Powerup_Speed_onDraw(Object *obj, PowerupSpeedData *data)
{
	ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURE, Object_getPos(obj), SCL * ASP_RAT, SCL, data->rotation, data->alpha);
}

void Powerup_Speed_update(Object* obj, PowerupSpeedData *data, float dt)
{
	UNREFERENCED_PARAMETER(obj);
	data->rotation -= dt;
}

void Powerup_Speed_onCollision(Collider *self, Collider *other)
{
	if (strcmp(Object_getName(other->gameObject), "Player"))
		return;
	Pedestal_resetPowerup(((PowerupSpeedData *)Object_getData(self->gameObject))->parent);

	BoostPlayer(other->gameObject);

	ObjectManager_delObj(self->gameObject);
}

typedef struct
{
	Object *player;
	float timer;
	float speedDiff;
}BoostData;

void BoostPlayer_update(Object* obj, BoostData *data, float dt)
{
	data->timer -= dt;
	if (data->timer <= 0.f)
	{
		((PlayerData *)Object_getData(obj))->speed -= data->speedDiff;
		ObjectManager_delObj(obj);
	}
}


static void BoostPlayer(Object *player)
{
	BoostData *data = malloc(sizeof(BoostData));
	data->player = player;
	data->timer = DURATION;
	data->speedDiff = (float)(((PlayerData *)Object_getData(player))->speed * 1.4 - ((PlayerData *)Object_getData(player))->speed);
	((PlayerData *)Object_getData(player))->speed *= SPEED_BONUS;
	ObjectManager_addObj(Object_new(NULL, BoostPlayer_update, NULL, data, free, "BoostSpeed"));
}

Object *Powerup_Speed_new(AEVec2 pos, Object *parent)
{
	PowerupSpeedData *data = malloc(sizeof(PowerupSpeedData));

	data->parent = parent;
	data->alpha = 1.f;
	data->rotation = 0.f;

	Object *power = Object_new(NULL, Powerup_Speed_update, Powerup_Speed_onDraw, data, free, "Powerup_Speed");
	CollisionHandler_Create_Circle_Collider(power, SCL / 2, 0, Powerup_Speed_onCollision);
	Object_setPos(power, pos);

	return power;
}
