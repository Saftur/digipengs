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

typedef struct PlayerData
{
    float direction;  ///< From -1 to 1;

    AEGfxVertexList *mesh;    ///< Mesh
    AEGfxTexture    *texture; ///< Texture

    float alpha; ///< Transparency
}PlayerData;

void Player_shutdown()
{

}


void Player_onInit(Object *obj, void *data)
{
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
}

void Player_onUpdate(Object *obj, void *data, float dt)
{
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
    UNREFERENCED_PARAMETER(dt);
}

void Player_onDraw(Object *obj, PlayerData *data)
{
    ImageHandler_fullDrawTexture(data->mesh, data->texture, Object_getPos(obj), PLAYER_SCALE, data->direction, data->alpha);
}


Object *Player_new(AEVec2 pos)
{
    PlayerData *data = calloc(1, sizeof(PlayerData));
    Object *player = Object_new(Player_onInit, Player_onUpdate, Player_onDraw, data, NULL);
    Object_setPos(player, pos);
    return player;
}

float Player_getDirection(Object * player);

void Player_setDirection(Object * player, float dir);

void Player_changeTexture(Object * player, AEGfxTexture texture);
