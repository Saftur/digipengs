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
#include "Utils.h"

#define POLARBEAR_DEFAULT_SIZE 1
#define POLARBEAR_INCREMENT    (POLARBEAR_DEFAULT_SIZE / 4)
#define POLARBEAR_DECREMENT    (POLARBEAR_DEFAULT_SIZE / 8)

#define POLARBEAR_ACCEL_MIN                100.0f
#define POLARBEAR_ACCEL_MAX                200.0f

#define POLARBEAR_SPEED_MAX 300.0f

#define POLARBEAR_RANGE_MIN        100
#define POLARBEAR_RANGE_MAX        450
#define POLARBEAR_MAX_DISTANCE_MIN 300
#define POLARBEAR_MAX_DISTANCE_MAX 500

#define POLARBEAR_HOME_DISTANCE_EPISLON 100

#define POLARBEAR_RANGE_SQUARED_MIN        (POLARBEAR_RANGE_MIN * POLARBEAR_RANGE_MIN)
#define POLARBEAR_RANGE_SQUARED_MAX        (POLARBEAR_RANGE_MAX * POLARBEAR_RANGE_MAX)
#define POLARBEAR_MAX_DISTANCE_SQUARED_MIN (POLARBEAR_MAX_DISTANCE_MIN * POLARBEAR_MAX_DISTANCE_MIN)
#define POLARBEAR_MAX_DISTANCE_SQUARED_MAX (POLARBEAR_MAX_DISTANCE_MAX * POLARBEAR_MAX_DISTANCE_MAX)

#define POLARBEAR_ROTATION_SPEED(size) (5 * POLARBEAR_DEFAULT_SIZE / size)

#define POLARBEAR_TEXTURE TEXTURES.polarbear

#define POLARBEAR_TIMER 0.25f

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

    float acceleration;
    float size;
    float rangeSquared;

    float rotation;
    float rotationSpeed;

    Object *target;
    float velocity;

    AEVec2 home;
    float maxDistanceSquared;

    float timer;
}PolarbearData;

void Polarbear_onDraw(Object *obj, PolarbearData *data)
{
    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), POLARBEAR_TEXTURE, Object_getPos(obj), data->size * POLARBEAR_ASPECT_RATIO, data->size, data->rotation, 1.0f);
}

void Polarbear_onInit(Object *obj, PolarbearData *data)
{
    UNREFERENCED_PARAMETER(obj);
    data->state = IDLE;
    data->rotation = 0;
    data->target = NULL;
    data->velocity = 0;
    data->timer = POLARBEAR_TIMER;
}

void Polarbear_onUpdate(Object *obj, PolarbearData *data, float dt)
{
    UNREFERENCED_PARAMETER(dt);
    switch (data->state)
    {
    case IDLE:
    {
        unsigned i;
        if (data->timer <= 0)
        {
            data->timer = POLARBEAR_TIMER;
            for (i = 0; i < ObjectManager_numObjs(); i++)
            {
                Object *player = ObjectManager_getObj(i);
                if (strcmp(Object_getName(player), "Player")) continue;
                AEVec2 playerPos = Object_getPos(player);
                AEVec2 objPos = Object_getPos(obj);
                if (AEVec2SquareDistance(&playerPos, &objPos) > data->rangeSquared) continue;
                data->velocity = 0;
                data->state = CHASING;
                data->target = player;
            }
        }
        else
            data->timer -= dt;
        break;
    }
    case CHASING:
    {
        AEVec2 objPos = Object_getPos(obj);
        
        if (AEVec2SquareDistance(&objPos, &data->home) > data->maxDistanceSquared) data->state = RETURNING;

        AEVec2 dir;
        AEVec2 targetPos = Object_getPos(data->target);
        AEVec2Sub(&dir, &targetPos, &objPos);
        AEVec2Normalize(&dir, &dir);

        data->rotation = rad_lerpf(data->rotation, AEVec2AngleFromVec2(&dir), data->rotationSpeed * dt);


        data->velocity += data->acceleration * dt;

        data->velocity = AEMin(data->velocity, POLARBEAR_SPEED_MAX);

        AEVec2Scale(&dir, &dir, data->velocity * dt);

        AEVec2Add(&objPos, &objPos, &dir);
        Object_setPos(obj, objPos); 

        break;
    }
    case RETURNING:
    {
        AEVec2 objPos = Object_getPos(obj);

        if (AEVec2SquareDistance(&objPos, &data->home) < POLARBEAR_HOME_DISTANCE_EPISLON) data->state = IDLE;

        AEVec2 dir;
        AEVec2Sub(&dir, &data->home, &objPos);
        AEVec2Normalize(&dir, &dir);

        data->rotation = rad_lerpf(data->rotation, AEVec2AngleFromVec2(&dir), data->rotationSpeed * dt);


        data->velocity += data->acceleration * dt;

        data->velocity = AEMin(data->velocity, POLARBEAR_SPEED_MAX);

        AEVec2Scale(&dir, &dir, data->velocity * dt);

        AEVec2Add(&objPos, &objPos, &dir);
        Object_setPos(obj, objPos);
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

    pData->acceleration = float_rand(POLARBEAR_ACCEL_MIN, POLARBEAR_ACCEL_MAX);
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


void Polarbear_setReturn(Object* polarbear)
{
    ((PolarbearData*)Object_getData(polarbear))->state = RETURNING;
}
