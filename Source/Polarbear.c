/**
 * @file Polarbear.c
 * @author Connor Meyers
 * @brief Object implementation for the Polarbear obstacle
 */

#include "stdafx.h"

#include "Polarbear.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "objectmanager.h"

static float float_rand(float min, float max);

typedef enum PolarbearStates
{
    IDLE,
    CHASING,
    RETURNING,
}PolarbearStates;

typedef struct PolarbearData
{
    PolarbearStates state;

    float speed;
    float size;
    float rangeSquared;

    float rotation;
    float targetRotation;
    float rotationSpeed;

    AEVec2 home;
    float maxDistanceSquared;
}PolarbearData;

void Polarbear_onDraw(Object *obj, PolarbearData *data)
{
    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.player, Object_getPos(obj), data->size, 0, 1.0f);
}


void Polarbear_onInit(Object *obj, PolarbearData *data)
{
    UNREFERENCED_PARAMETER(obj);
    data->state = IDLE;
    data->rotation = 0;
    data->targetRotation = 0;
}

void Polarbear_onUpdate(Object *obj, PolarbearData *data, float dt)
{
    UNREFERENCED_PARAMETER(dt);
    switch (data->state)
    {
    case IDLE:
    {
        int i;
        for (i = 0; i < (int)ObjectManager_numObjs(); i++)
        {
            Object *player = ObjectManager_getObj(i);
            if (strcmp(Object_getName(player), "Player")) continue;
            AEVec2 playerPos = Object_getPos(player);
            AEVec2 objPos = Object_getPos(obj);
            if (AEVec2SquareDistance(&playerPos, &objPos) > data->rangeSquared) continue;
            data->state = CHASING;
            AEVec2 dir;
            AEVec2Sub(&dir, &playerPos, &objPos);
            AEVec2Normalize(&dir, &dir);
            data->targetRotation = AEVec2AngleFromVec2(&dir);
        }
        break;
    }
    case CHASING:
    {

        break;
    }
    } /*Switch Statement*/
}

void Polarbear_decrementSize(Object* polarbear)
{
    ((PolarbearData*)Object_getData(polarbear))->size -= (float)POLARBEAR_DECREMENT;
}

void Polarbear_incrementSize(Object* polarbear)
{
    ((PolarbearData*)Object_getData(polarbear))->size += (float)POLARBEAR_INCREMENT;
}


void Polarbear_setSize(Object * polarbear, float value)
{
    ((PolarbearData*)Object_getData(polarbear))->size = value;
}

float Polarbear_getSize(Object * polarbear)
{
    return ((PolarbearData*)Object_getData(polarbear))->size;
}

Object *Polarbear_new(AEVec2 pos)
{
    PolarbearData *pData = malloc(sizeof(PolarbearData));
    if (!pData) return NULL;

    pData->speed = float_rand(POLARBEAR_SPEED_MIN, POLARBEAR_SPEED_MAX);
    pData->size = (float)POLARBEAR_DEFAULT_SIZE;
    pData->rangeSquared = float_rand(POLARBEAR_RANGE_SQUARED_MIN, POLARBEAR_RANGE_SQUARED_MAX);
    pData->rotationSpeed = POLARBEAR_ROTATION_SPEED(pData->size);
    pData->home = pos;
    pData->maxDistanceSquared = float_rand(POLARBEAR_MAX_DISTANCE_SQUARED_MIN, POLARBEAR_MAX_DISTANCE_SQUARED_MAX);

    Object *polarbear = Object_new(Polarbear_onInit, Polarbear_onUpdate, Polarbear_onDraw, pData, free, "Polarbear");
    Object_setPos(polarbear, pos);
    return polarbear;
}

static float float_rand(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);      /* [min, max] */
}