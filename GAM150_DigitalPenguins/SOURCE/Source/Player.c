/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
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
#include "Leaderboard.h"
#include "LeaderboardData.h"
#include "Timer.h"
#include "LapCounter.h"
#include "objectmanager.h"
#include "CollisionHandler.h"
#include "CollisionEvents.h"
#include "PlayerParticles.h"

#define PLAYER_ACCEL 240.75f
#define PLAYER_DECCEL 252.f
#define PLAYER_MAXSPD 420.f
#define PLAYER_ROTSPD 3.f

void Player_onInit(Object *obj, PlayerData *data)
{
    UNREFERENCED_PARAMETER(obj);
    data->speed = 0.f;
    Map_initCamera(Camera_get(data->playerNum), Object_getPos(obj), 90.f - AERadToDeg(data->direction));
	data->collider = CollisionHandler_Create_Circle_Collider(obj, fmaxf(PLAYER_SCALE.x, PLAYER_SCALE.y) / 2, 0, PlayerOnCollision);
}

void Player_onShutdown(PlayerData *data) {
    //AEGfxMeshFree(data->mesh);
    ParticleEmitter_delete(data->particleEmitter);
    free(data->particleData);
    free(data);
}

void Player_onUpdate(Object *obj, PlayerData *data, float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (!GameStartTimer_started())
		return;

	data->alpha = 1.f - min(data->collider->phase, 0.8f) ;
	if (!(data->finished))
		Timer_Start(Object_getData(data->timer));

	if (data->lap == NUM_LAPS && data->currentLap == NUM_LAPS)
	{
		FinalLap_display(data->playerNum);
		data->currentLap++;
	}
	else if (data->lap == NUM_LAPS - 1 && data->currentLap == NUM_LAPS - 1)
	{
		LapsLeftDisplay_display(data->playerNum, 2);
		data->currentLap++;
	}
	else if (data->lap == NUM_LAPS - 2 && data->currentLap == NUM_LAPS - 2)
	{
		data->currentLap++;
	}

    if (data->lap >= NUM_LAPS+1) 
	{
		if (data->finished == false)
		{
			data->finished = true;
			Timer_Stop(Object_getData(data->timer));

			if (splitScreen) {
				EndScreen_winner = data->playerNum + 1;
			}
			else EndScreen_winner = 0;

			Timer* timerData = Object_getData(data->timer);

			data->playerRank = Leaderboard_addEntry("[insert name]       ", timerData->time, timerData->intTime / 60, timerData->intTime % 60);
			data->leaderboard = Default_Leaderboard(data->playerNum, data->playerRank);

			AEInputShowCursor(true);
		}
    }
	if(data->speed < data->speedcap)
		data->speed += data->acceleration * data->speedScalar * dt;

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
    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), 
		data->texture, Object_getPos(obj), PLAYER_SCALE.x, PLAYER_SCALE.y, data->direction, data->alpha);
}


Object *Player_new(AEVec2 pos, float direction, Controls controls, unsigned playerNum)
{
    PlayerData * data = calloc(1, sizeof(PlayerData));
    Object *player = Object_new(Player_onInit, Player_onUpdate, Player_onDraw, data, Player_onShutdown, "Player");
    Object_setPos(player, pos);
    data->direction = direction;
	data->acceleration = PLAYER_ACCEL;
	data->deceleration = PLAYER_DECCEL;
    data->speedcap = PLAYER_MAXSPD;
    data->speedScalar = 1;

	data->lap = 1.0f;

    data->controls = controls;

    data->texture = PLAYER_STANDARD_TEXTURE;

    data->playerNum = playerNum;

    data->alpha = 1.0f;

	data->currentLap = 1;
	data->finished = false;
	data->highscore = false;
	data->typingName = false;

	//strcpy(data->name, "[insert name]       ");
	data->nameIndex = 0;

    data->particleData = malloc(sizeof(PlayerParticleData));
    ((PlayerParticleData*)data->particleData)->playerData = data;
    ((PlayerParticleData*)data->particleData)->modeSwitch = 0;
    data->particleEmitter = ParticleEmitter_new(pos, direction, 1, 16, particleSpawnFunc, particleSpawnTimeFunc, data->particleData);

	AEVec2 timerPos;
	timerPos.x = (splitScreen ? AEGfxGetWinMinX() / 2.f : AEGfxGetWinMinX()) + 30.f;
	timerPos.y = AEGfxGetWinMaxY() - 80.f;
	Object *timer = Timer_new(playerNum, TEXTURES.font, timerPos, (AEVec2) { 23, 42 }, 0);
	data->timer = timer;
	ObjectManager_addObj(timer);

	AEVec2 lapCounterPos;
	lapCounterPos.x = (splitScreen ? AEGfxGetWinMinX() / 2.f : AEGfxGetWinMinX()) + 40.f;
	lapCounterPos.y = AEGfxGetWinMaxY() - 40.f;
	Object *lapCounter = LapCounter_new(playerNum, "Lap %d", TEXTURES.font, lapCounterPos, (AEVec2) { 23, 42 }, &(data->lap));
	data->lapCounter = lapCounter;
	ObjectManager_addObj(lapCounter);

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
