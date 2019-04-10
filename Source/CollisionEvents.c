/**
 * @file CollisionEvents.c
 * @author Brand Knutson
 * @date 1/23/2019
 * @brief OnCollision functions.
 */

#include "stdafx.h"
#include "CollisionEvents.h"
#include "object.h"
#include "Player.h"
#include "Polarbear.h"
#include "Map.h"

void PlayerOnCollision(Collider *self, Collider *other) {
    PlayerData *data = (PlayerData*)Object_getData(self->gameObject);
    if(!strcmp("Boulder", Object_getName(other->gameObject)))
    {
        Player_resetSpeed(data);
        CollisionHandler_SetPhaseDuration(self->gameObject, 2);
    }

    if (!strcmp("Polarbear", Object_getName(other->gameObject)))
    {
        Player_resetSpeed(data);
        Polarbear_setReturn(other->gameObject);
        CollisionHandler_SetPhaseDuration(self->gameObject, 2);
    }

    if(!strcmp("Wall", Object_getName(other->gameObject)))
    {
        AEVec2 playerPos = Object_getPos(self->gameObject);
        unsigned tileX, tileY;
        AEVec2 tileWorldPos;
        Map_worldPosToTilePos(&tileX, &tileY, playerPos.x, playerPos.y);
        Tile *tile = Map_getTile(tileX, tileY);
        Map_tilePosToWorldPos(&tileWorldPos.x, &tileWorldPos.y, tileX, tileY);
        AEVec2 direction;
        //If the tile is a straight segment.
        if (tile->from == SDown && tile->to == SUp || tile->from == SUp && tile->to == SDown
            || tile->from == SLeft && tile->to == SRight || tile->from == SRight && tile->to == SLeft) {
            if (tile->to == SUp || tile->to == SDown) {
                AEVec2 wallPos = Object_getPos(other->gameObject);
                AEVec2Sub(&direction, &tileWorldPos, &wallPos);
            }
            else if (tile->to == SLeft || tile->to == SRight) {
                AEVec2 wallPos = Object_getPos(other->gameObject);
                AEVec2Sub(&direction, &tileWorldPos, &wallPos);
            }
        }
        else {
            //Upper left corner.
            if ((tile->from == SDown && tile->to == SRight) || (tile->from == SRight && tile->to == SDown)) {
                if (other->type == Circle) {
                    AEVec2 wallPos = Object_getPos(other->gameObject);
                    AEVec2Sub(&direction, &tileWorldPos, &wallPos);
                }
                else {
                    AEVec2 wallPos = Object_getPos(other->gameObject);
                    tileWorldPos.x = tileWorldPos.x + TILE_SIZE / 2;
                    tileWorldPos.y = tileWorldPos.y - TILE_SIZE / 2;
                    AEVec2Sub(&direction, &tileWorldPos, &wallPos);
                }
            }
            //Upper right corner.
            if ((tile->from == SDown && tile->to == SLeft) || (tile->from == SLeft && tile->to == SDown)) {
                if (other->type == Circle) {
                    AEVec2 wallPos = Object_getPos(other->gameObject);
                    AEVec2Sub(&direction, &tileWorldPos, &wallPos);
                }
                else {
                    AEVec2 wallPos = Object_getPos(other->gameObject);
                    tileWorldPos.x = tileWorldPos.x - TILE_SIZE / 2;
                    tileWorldPos.y = tileWorldPos.y - TILE_SIZE / 2;
                    AEVec2Sub(&direction, &tileWorldPos, &wallPos);
                }
            }
            //Lower right corner.
            if ((tile->from == SLeft && tile->to == SUp) || (tile->from == SUp && tile->to == SLeft)) {
                if (other->type == Circle) {
                    AEVec2 wallPos = Object_getPos(other->gameObject);
                    AEVec2Sub(&direction, &tileWorldPos, &wallPos);
                }
                else {
                    AEVec2 wallPos = Object_getPos(other->gameObject);
                    tileWorldPos.x = tileWorldPos.x - TILE_SIZE / 2;
                    tileWorldPos.y = tileWorldPos.y + TILE_SIZE / 2;
                    AEVec2Sub(&direction, &tileWorldPos, &wallPos);
                }
            }
            //Lower left corner.
            if ((tile->from == SRight && tile->to == SUp) || (tile->from == SUp && tile->to == SRight)) {
                if (other->type == Circle) {
                    AEVec2 wallPos = Object_getPos(other->gameObject);
                    AEVec2Sub(&direction, &tileWorldPos, &wallPos);
                }
                else {
                    AEVec2 wallPos = Object_getPos(other->gameObject);
                    tileWorldPos.x = tileWorldPos.x + TILE_SIZE / 2;
                    tileWorldPos.y = tileWorldPos.y + TILE_SIZE / 2;
                    AEVec2Sub(&direction, &tileWorldPos, &wallPos);
                }
            }
        }

        AEVec2 newPos;
        AEVec2Normalize(&direction, &direction);
        AEVec2Scale(&direction, &direction, data->speed * 0.0167f);
        data->speed *= 0.9f;
        AEVec2Add(&newPos, &playerPos, &direction);
        Object_setPos(self->gameObject, newPos);
        //if (data->speed) data->speed *= 1;
    }
}

void StartLineOnCollision(Collider *self, Collider *other) {
    UNREFERENCED_PARAMETER(self);
    if (strcmp(Object_getName(other->gameObject), "Player"))
        return;
    PlayerData *player = Object_getData(other->gameObject);
    if (player->lap != floorf(player->lap))
        player->lap += 0.5f;
}

void CheckpointOnCollision(Collider *self, Collider *other) {
    UNREFERENCED_PARAMETER(self);
    if (strcmp(Object_getName(other->gameObject), "Player"))
        return;
    PlayerData *player = Object_getData(other->gameObject);
    if (player->lap == floorf(player->lap))
        player->lap += 0.5f;
}
