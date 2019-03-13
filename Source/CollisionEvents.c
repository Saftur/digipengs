/**
 * @file CollisionEvents.c
 * @author Brand Knutson
 * @date 1/23/2019
 * @brief All OnCollision functions.
 */

#include "stdafx.h"
#include "CollisionEvents.h"
#include "object.h"
#include "Player.h"

void PlayerOnCollision(Collider *self, Collider *other) {
    PlayerData *data = (PlayerData*)Object_getData(self->gameObject);
    if(!strcmp("Boulder", Object_getName(other->gameObject)))
    {
        Player_resetSpeed(data);
        CollisionHandler_SetPhaseDuration(self->gameObject, 2);
    }

    if(!strcmp("Wall", Object_getName(other->gameObject)))
    {
        //Call Player Slow Down Function.
        Player_resetSpeed(data);

        AEVec2 playerPos = Object_getPos(self->gameObject);
        AEVec2 wallPos = Object_getPos(other->gameObject);

        AEVec2 direction;
        direction.x = playerPos.x - wallPos.x;
        direction.y = playerPos.y - wallPos.y;
        AEVec2Normalize(&direction, &direction);

        float repelDistance = 1;
        AEVec2Scale(&direction, &direction, repelDistance);

        AEVec2 newPlayerPos;
        AEVec2Add(&newPlayerPos, &playerPos, &direction);

        Object_setPos(self->gameObject, newPlayerPos);
    }
}

void StartLineOnCollision(Collider *self, Collider *other) {
    UNREFERENCED_PARAMETER(self);
    if (strcmp(Object_getName(other->gameObject), "Player"))
        return;
    PlayerData *player = Object_getData(other->gameObject);
    if ( *(player->lap) != floorf( *(player->lap) ))
        *(player->lap) += 0.5f;
}

void CheckpointOnCollision(Collider *self, Collider *other) {
    UNREFERENCED_PARAMETER(self);
    if (strcmp(Object_getName(other->gameObject), "Player"))
        return;
    PlayerData *player = Object_getData(other->gameObject);
    if ( *(player->lap) == floorf( *(player->lap) ))
        *(player->lap) += 0.5f;
}
