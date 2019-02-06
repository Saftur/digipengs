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
    data->mesh = MeshHandler_createSquareMesh(PLAYER_SCALE.x, PLAYER_SCALE.y);
    data->texture = PLAYER_STANDARD_TEXTURE;
	data->acceleration = 0.046875f;
    data->speedcap = 6.0f;
}

void Player_onUpdate(Object *obj, PlayerData *data, float dt)
{
    UNREFERENCED_PARAMETER(dt);

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
		Player_resetSpeed(data);

	AEVec2 pos = Object_getPos(obj);
	pos.x += (data->speed * cosf(data->direction));
	pos.y += (data->speed * sinf(data->direction));

    /*if (Input_upCheck(data->controls))
        pos.y += 2.f;
    if (Input_downCheck(data->controls))
        pos.y -= 2.f;
    if (Input_leftCheck(data->controls))
        pos.x -= 2.f;
    if (Input_rightCheck(data->controls))
        pos.x += 2.f;*/
	Object_setPos(obj, pos);

    Camera *cam = Camera_get(data->camNum);
    unsigned tx, ty;
    Map_worldPosToTilePos(&tx, &ty, pos.x, pos.y);
    float twx, twy;
    Map_tilePosToWorldPos(&twx, &twy, tx, ty);
    Tile tile = Map_getTile(tx, ty);

    switch (tile.type) {
    case TTHoriz:
        cam->worldPos.y = twy;
        cam->worldPos.x = pos.x;
        cam->worldRot = (tile.from == SLeft ? 90.f : -90.f);
        break;
    case TTVert:
        cam->worldPos.x = twx;
        cam->worldPos.y = pos.y;
        cam->worldRot = (tile.from == SDown ? 0.f : 180.f);
        break;
    case TTTurn: {
        AEVec2 localPos;
        AEVec2 point;
        if (tile.from == SRight && tile.to == SDown ||
            tile.from == SDown && tile.to == SRight) {
            point.x = twx + TILE_SIZE / 2.f;
            point.y = twy - TILE_SIZE / 2.f;
        }
        if (tile.from == SLeft && tile.to == SDown ||
            tile.from == SDown && tile.to == SLeft) {
            point.x = twx - TILE_SIZE / 2.f;
            point.y = twy - TILE_SIZE / 2.f;
        }
        if (tile.from == SRight && tile.to == SUp ||
            tile.from == SUp && tile.to == SRight) {
            point.x = twx + TILE_SIZE / 2.f;
            point.y = twy + TILE_SIZE / 2.f;
        }
        if (tile.from == SLeft && tile.to == SUp ||
            tile.from == SUp && tile.to == SLeft) {
            point.x = twx - TILE_SIZE / 2.f;
            point.y = twy + TILE_SIZE / 2.f;
        }
        AEVec2Sub(&localPos, &pos, &point);
        AEVec2Scale(&localPos, &localPos, (TILE_SIZE / 2.f) / AEVec2Length(&localPos));
        AEVec2Add(&cam->worldPos, &localPos, &point);
        cam->worldRot = -AERadToDeg(AEVec2AngleFromVec2(&localPos));
        break;
    }
    }
}

void Player_onDraw(Object *obj, PlayerData *data)
{
    ImageHandler_fullDrawTexture(data->mesh, data->texture, Object_getPos(obj), 1.0f, data->direction, data->alpha);
}


Object *Player_new(AEVec2 pos, Controls controls, unsigned camNum)
{
    PlayerData * data = calloc(1, sizeof(PlayerData));
    Object *player = Object_new(Player_onInit, Player_onUpdate, Player_onDraw, data, Player_onShutdown, "Player");
    Object_setPos(player, pos);
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