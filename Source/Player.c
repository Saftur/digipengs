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
#include "Level2.h"
#include "EndScreen.h"
#include "Utils.h"
#include "GameStartTimer.h"
#include "FinalLap.h"

#define PLAYER_ACCEL 240.75f
#define PLAYER_DECCEL 252.f
#define PLAYER_MAXSPD 420.f
#define PLAYER_ROTSPD 3.f

static Particle *particleSpawnFunc();
static float particleSpawnTimeFunc();

void Player_onInit(Object *obj, PlayerData *data)
{
    UNREFERENCED_PARAMETER(obj);
    data->speed = 0.f;

    Map_initCamera(Camera_get(data->playerNum), Object_getPos(obj));
}

void Player_onShutdown(PlayerData *data) {
    AEGfxMeshFree(data->mesh);
    ParticleEmitter_delete(data->particleEmitter);
    free(data);
}

void Player_onUpdate(Object *obj, PlayerData *data, float dt)
{
	if (!GameStartTimer_started())
		return;
    UNREFERENCED_PARAMETER(dt);

	if (*(data->lap) == NUM_LAPS && !data->finalLap)
	{
		FinalLap_display(data->playerNum);
		data->finalLap = 1;
	}

    if (*(data->lap) >= NUM_LAPS+1) {
        if (splitScreen) {
            EndScreen_winner = data->playerNum + 1;
        } else EndScreen_winner = 0;
        LevelManager_setNextLevel(EndScreen);
        return;
    }

	data->speed += data->acceleration * dt;
	data->speed = fminf(data->speed, data->speedcap);

	if (Input_leftCheck(data->controls))
	{
		data->direction += PLAYER_ROTSPD * dt;
	}

	if (Input_rightCheck(data->controls))
	{
		data->direction -= PLAYER_ROTSPD * dt;
	}
	
	if (Input_downCheck(data->controls))
	{
		data->speed -= (data->acceleration + data->deceleration) * dt;
		data->speed = fmaxf(data->speed, 0);
	}

	AEVec2 pos = Object_getPos(obj);
	pos.x += data->speed * cosf(data->direction) * dt;
	pos.y += data->speed * sinf(data->direction) * dt;

	Object_setPos(obj, pos);

    Map_updateCamera(Camera_get(data->playerNum), pos);

    data->particleEmitter->pos = pos;
    data->particleEmitter->rot = data->direction;
    ParticleEmitter_update(data->particleEmitter, dt);
}

void Player_onDraw(Object *obj, PlayerData *data)
{
    ParticleEmitter_draw(data->particleEmitter);
    ImageHandler_fullDrawTexture(data->mesh, data->texture, Object_getPos(obj), 1.0f, 1.0f, data->direction, data->alpha);
}


Object *Player_new(AEVec2 pos, float direction, Controls controls, unsigned playerNum, float* lap)
{
    PlayerData * data = calloc(1, sizeof(PlayerData));
    Object *player = Object_new(Player_onInit, Player_onUpdate, Player_onDraw, data, Player_onShutdown, "Player");
    Object_setPos(player, pos);
    data->direction = direction;
	data->acceleration = PLAYER_ACCEL;
	data->deceleration = PLAYER_DECCEL;
    data->speedcap = PLAYER_MAXSPD;

	data->lap = lap;

    data->controls = controls;

    data->mesh = MeshHandler_createSquareMesh(PLAYER_SCALE.x, PLAYER_SCALE.y, 1, 1);
    data->texture = PLAYER_STANDARD_TEXTURE;

    data->playerNum = playerNum;

    data->alpha = 1.0f;

	data->finalLap = false;

    data->particleEmitter = ParticleEmitter_new(pos, direction, 1, 16, particleSpawnFunc, particleSpawnTimeFunc);

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

static Particle *particleSpawnFunc() {
    Particle *p = Particle_new();

    p->pos.x = -PLAYER_SCALE.x / 4.f;

    float rot = randrangef(0.5f * PI, 1.5f * PI);
    AEVec2FromAngle(&p->vel, rot);
    AEVec2Scale(&p->vel, &p->vel, randrangef(100, 150));

    p->rotVel = 2.f * PI;

    p->life = 0.25f;

    p->scl.x = 15.f;
    p->scl.y = 15.f;
    p->sclChange.x = -p->scl.x / p->life;
    p->sclChange.y = -p->scl.y / p->life;

    p->texture = TEXTURES.particle;

    return p;
}

static float particleSpawnTimeFunc() {
    return 0.05f;
}
