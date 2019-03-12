/**
 * @file Player.h
 * @author Connor Meyers
 * @date 2019/01/30
 * @brief Object * Header for the Player
 */

#include "stdafx.h"

#include "Player.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "LevelManager.h"
#include "Object.h"
#include "Camera.h"
#include "Map.h"

void Player_onShutdown(PlayerData *data) {
    AEGfxMeshFree(data->mesh);
    free(data);
}

void Player_onInit(Object *obj, PlayerData *data)
{
    UNREFERENCED_PARAMETER(obj);
    data->alpha = 1.0f;
    data->mesh = MeshHandler_createSquareMesh(PLAYER_SCALE.x, PLAYER_SCALE.y, 1, 1);
    data->texture = PLAYER_STANDARD_TEXTURE;
	data->acceleration = 0.046875f;
	data->deceleration = 0.05f;
    data->speedcap = 6.0f;
    data->lap = 1.f;

    Map_initCamera(Camera_get(data->camNum), Object_getPos(obj));
}

void Player_onUpdate(Object *obj, PlayerData *data, float dt)
{
    UNREFERENCED_PARAMETER(dt);

    if (data->lap >= 4.f) {
        LevelManager_setNextLevel(TitleScreen);
        return;
    }

	data->speed += data->acceleration;
	data->speed = fminf(data->speed, data->speedcap);

	if (Input_leftCheck(data->controls))
	{
		data->direction += 0.05f;
	}

	if (Input_rightCheck(data->controls))
	{
		data->direction -= 0.05f;
	}
	
	if (Input_downCheck(data->controls))
	{
		data->speed -= (data->acceleration + data->deceleration);
		data->speed = fmaxf(data->speed, 0);
	}

	AEVec2 pos = Object_getPos(obj);
	pos.x += (data->speed * cosf(data->direction));
	pos.y += (data->speed * sinf(data->direction));

	Object_setPos(obj, pos);

    Map_updateCamera(Camera_get(data->camNum), pos);
}

void Player_onDraw(Object *obj, PlayerData *data)
{
    ImageHandler_fullDrawTexture(data->mesh, data->texture, Object_getPos(obj), 1.0f, 1.0f, data->direction, data->alpha);
}


Object *Player_new(AEVec2 pos, float direction, Controls controls, unsigned camNum)
{
    PlayerData * data = calloc(1, sizeof(PlayerData));
    Object *player = Object_new(Player_onInit, Player_onUpdate, Player_onDraw, data, Player_onShutdown, "Player");
    Object_setPos(player, pos);
    data->direction = direction;
    data->camNum = camNum;
    data->controls = controls;
    return player;
}

float Player_getDirection(Object * player)
{
    return ((PlayerData*)Object_getData(player))->direction;
}

void Player_setDirection(Object * player, float dir)
{
    ((PlayerData*)Object_getData(player))->direction = dir;
}

void Player_changeTexture(Object * player, AEGfxTexture * texture)
{
    ((PlayerData*)Object_getData(player))->texture = texture;
}

float Player_getAlpha(Object * player)
{
    return ((PlayerData*)Object_getData(player))->alpha;
}

void Player_setAlpha(Object * player, float alpha)
{
    ((PlayerData*)Object_getData(player))->alpha = alpha;
}

void Player_resetSpeed(PlayerData *data)
{
	data->speed = 0.0f;
}
