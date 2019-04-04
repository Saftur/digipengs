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
#include "LapsLeftDisplay.h"

#define PLAYER_ACCEL 240.75f
#define PLAYER_DECCEL 252.f
#define PLAYER_MAXSPD 420.f
#define PLAYER_ROTSPD 3.f

typedef struct PlayerParticleData {
    PlayerData *playerData;
    int modeSwitch;
} PlayerParticleData;

static Particle *particleSpawnFunc(PlayerParticleData *data);
static float particleSpawnTimeFunc(PlayerParticleData *data);

void Player_onInit(Object *obj, PlayerData *data)
{
    UNREFERENCED_PARAMETER(obj);
    data->speed = 0.f;
    Map_initCamera(Camera_get(data->playerNum), Object_getPos(obj), 90.f - AERadToDeg(data->direction));
}

void Player_onShutdown(PlayerData *data) {
    //AEGfxMeshFree(data->mesh);
    ParticleEmitter_delete(data->particleEmitter);
    free(data->particleData);
    free(data);
}

void Player_onUpdate(Object *obj, PlayerData *data, float dt)
{
	if (!GameStartTimer_started())
		return;
    UNREFERENCED_PARAMETER(dt);

	if (*(data->lap) == NUM_LAPS && data->currentLap == NUM_LAPS)
	{
		FinalLap_display(data->playerNum);
		data->currentLap++;
	}
	else if (*(data->lap) == NUM_LAPS - 1 && data->currentLap == NUM_LAPS - 1)
	{
		LapsLeftDisplay_display(data->playerNum, 2);
		data->currentLap++;
	}
	else if (*(data->lap) == NUM_LAPS - 2 && data->currentLap == NUM_LAPS - 2)
	{
		data->currentLap++;
	}

    if (*(data->lap) >= NUM_LAPS+1) {
        if (splitScreen) {
            EndScreen_winner = data->playerNum + 1;
        } else EndScreen_winner = 0;
        LevelManager_setNextLevel(EndScreen);
        return;
    }

	data->speed += data->acceleration * data->speedScalar * dt;
	data->speed = fminf(data->speed, data->speedcap * data->speedScalar);

	if (Input_leftCheck(data->controls))
	{
		data->direction += PLAYER_ROTSPD * data->speedScalar * dt;
	}

	if (Input_rightCheck(data->controls))
	{
		data->direction -= PLAYER_ROTSPD * data->speedScalar * dt;
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

    Map_updateCamera(Camera_get(data->playerNum), pos, 90.f - AERadToDeg(data->direction));

    data->particleEmitter->pos = pos;
    data->particleEmitter->rot = data->direction;
    ParticleEmitter_update(data->particleEmitter, dt);
}

void Player_onDraw(Object *obj, PlayerData *data)
{
    ParticleEmitter_draw(data->particleEmitter);
    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), data->texture, Object_getPos(obj), PLAYER_SCALE.x, PLAYER_SCALE.y, data->direction, data->alpha);
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
    data->speedScalar = 1;

	data->lap = lap;

    data->controls = controls;

    data->texture = PLAYER_STANDARD_TEXTURE;

    data->playerNum = playerNum;

    data->alpha = 1.0f;

	data->currentLap = 1;

    data->particleData = malloc(sizeof(PlayerParticleData));
    ((PlayerParticleData*)data->particleData)->playerData = data;
    ((PlayerParticleData*)data->particleData)->modeSwitch = 0;
    data->particleEmitter = ParticleEmitter_new(pos, direction, 1, 16, particleSpawnFunc, particleSpawnTimeFunc, data->particleData);

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

static Particle *particleSpawnFunc(PlayerParticleData *data) {
#define ROT_START       0.5f
#define ROT_START_LEFT  ROT_START
#define ROT_START_RIGHT (ROT_START + 1.f)
#define ROT_RANGE_UP    0.1f
#define ROT_RANGE_DOWN  0.1f
#define LIFE            0.25f
#define SCALE           15.f

    UNREFERENCED_PARAMETER(data);
    Particle *p = Particle_new();

    p->pos.x = data->modeSwitch / 2 < 1 ? -PLAYER_SCALE.x * 0.4f : PLAYER_SCALE.x * 0.125f;
    p->pos.y = 0.f;
    p->pos.y = (data->modeSwitch % 2 == 0 ? 1.f : -1.f) * PLAYER_SCALE.y * 0.125f;

    float rot = data->modeSwitch % 2 == 0 ? randrangef((ROT_START_LEFT - ROT_RANGE_UP) * PI, (ROT_START_LEFT + ROT_RANGE_DOWN) * PI) : 
                                            randrangef((ROT_START_RIGHT - ROT_RANGE_DOWN) * PI, (ROT_START_RIGHT + ROT_RANGE_UP) * PI);
    AEVec2FromAngle(&p->vel, rot);

    AEVec2 posAdd;
    AEVec2Scale(&posAdd, &p->vel, PLAYER_SCALE.y / 4.f);
    AEVec2Add(&p->pos, &p->pos, &posAdd);

    AEVec2Scale(&p->vel, &p->vel, randrangef(100, 150));

    AEVec2 velAdd;
    velAdd.x = data->playerData->speed * 0.75f;
    velAdd.y = 0.f;
    AEVec2Add(&p->vel, &p->vel, &velAdd);

    p->rotVel = 2.f * PI;

    p->life = LIFE;

    p->scl.x = SCALE;
    p->scl.y = SCALE;
    p->sclChange.x = -p->scl.x / p->life;
    p->sclChange.y = -p->scl.y / p->life;

    p->texture = TEXTURES.particle;

    data->modeSwitch = (data->modeSwitch + 1) % 4;

    return p;
#undef ROT_START
#undef ROT_START_LEFT
#undef ROT_START_RIGHT
#undef ROT_RANGE_UP
#undef ROT_RANGE_DOWN
#undef LIFE
#undef SCALE
}

static float particleSpawnTimeFunc(PlayerParticleData *data) {
    return data->playerData->speed / data->playerData->speedcap * 80.f;
}
