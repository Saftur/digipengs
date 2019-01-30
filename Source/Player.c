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
    AEVec2 transform;         ///< Position
    float direction;          ///< From -1 to 1;

    AEGfxVertexList *mesh;    ///< Mesh
    AEGfxTexture    *texture; ///< Texture
}PlayerData;

void Player_intialize();

void Player_shutdown();

Object *Player_new(PlayerData * data);

AEVec2 Player_getTransform(Object * player);

void Player_setTransform(Object * player, AEVec2 vec);

float Player_getDirection(Object * player);

void Player_setDirection(Object * player, float dir);

void Player_changeTexture(Object * player, AEGfxTexture texture);
