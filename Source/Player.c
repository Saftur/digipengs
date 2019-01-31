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

void Player_onShutdown(PlayerData *data)
{
    free(data);
}


void Player_onInit(Object *obj, PlayerData *data)
{
    UNREFERENCED_PARAMETER(obj);
    data->alpha = 1.0f;
    data->mesh = MeshHandler_createSquareMesh(PLAYER_SCALE.x, PLAYER_SCALE.y);
    data->texture = PLAYER_STANDARD_TEXTURE;
}

void Player_onUpdate(Object *obj, void *data, float dt)
{
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
    UNREFERENCED_PARAMETER(dt);
}

void Player_onDraw(Object *obj, PlayerData *data)
{
    ImageHandler_fullDrawTexture(data->mesh, data->texture, Object_getPos(obj), (AEVec2) { 1.0f , 1.0f }, data->direction, data->alpha);
}


Object *Player_new(AEVec2 pos)
{
    PlayerData * data = calloc(1, sizeof(PlayerData));
    Object *player = Object_new(Player_onInit, Player_onUpdate, Player_onDraw, data, Player_onShutdown);
    Object_setPos(player, pos);
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
