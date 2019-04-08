﻿/**
 * @file Level2.c
 * @author Arthur Bouvier
 * @date 1/30/2019
 * @brief Main Level
 */

#include "stdafx.h"
#include "AEEngine.h"
#include "Level2.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Player.h"
#include "Object.h"
#include "Map.h"
#include "CollisionHandler.h"
#include "CollisionEvents.h"
#include "AudioHandler.h"
#include "Camera.h"
#include "Polarbear.h"
#include "ObstacleManager.h"
#include "Utils.h"
#include "Timer.h"
#include "LapCounter.h"
#include "Background.h"
#include "GameStartTimer.h"

#define SCREEN_SEPARATOR_WIDTH 10

#define MP_PLAYER_OFFSET 64

Object *Player1 = NULL;
Object *Player2 = NULL;

float player1Lap;
float player2Lap;

int splitScreen = 0;

static void initPlayers();
static void separatorDraw(Object *obj, void *data);

void Level2_onLoad()
{
    Audio_playGameplay();
}

void Level2_onInit()
{
    AEInputShowCursor(0);

    //Draw Background
    ObjectManager_addObj(Background_create());


	if (splitScreen)
	{
		Camera_clear();
        AEVec2 size = AEGfxGetWinSize();
        size.x /= 2.f;
        AEVec2 posL = {0, 0};
        AEVec2 posR = {0, 0};
        posR.x = size.x;
		Camera_new((AEVec2) { 0, 0 }, 1.f, 0, posL, size);
		Camera_new((AEVec2) { 0, 0 }, 1.f, 0, posR, size);
	}

    Map_init("Assets\\Map.txt");
    ObstacleManager_loadObstacles();

    Tile *tile = Map_getStartTile();
    Tile *halfwayTile = tile;

    do {
        tile = Map_getNextTile(tile);
        if (tile->isStart)
            break;
        tile = Map_getNextTile(tile);
        halfwayTile = Map_getNextTile(halfwayTile);
    } while (!tile->isStart);

    Object *obj;
    AEVec2 pos;

    obj = Object_new(NULL, NULL, NULL, NULL, NULL, "Start");
    Map_tilePosToWorldPos(&pos.x, &pos.y, Map_getStartX(), Map_getStartY());
    AEVec2 size = (AEVec2) { 0.f, 0.f };
    if (tile->to == SLeft) {
        pos.x -= LANE_WIDTH;
        size = (AEVec2) { LANE_WIDTH * 2, TILE_SIZE };
    } else if (tile->to == SRight) {
        pos.x += LANE_WIDTH;
        size = (AEVec2) { LANE_WIDTH * 2, TILE_SIZE };
    } else if (tile->to == SUp) {
        pos.y += LANE_WIDTH;
        size = (AEVec2) { TILE_SIZE, LANE_WIDTH * 2 };
    } else if (tile->to == SDown) {
        pos.y -= LANE_WIDTH;
        size = (AEVec2) { TILE_SIZE, LANE_WIDTH * 2 };
    }
    Object_setPos(obj, pos);
    CollisionHandler_Create_Square_Collider(obj, size, 0, StartLineOnCollision);
    ObjectManager_addObj(obj);

    obj = Object_new(NULL, NULL, NULL, NULL, NULL, "Checkpoint");
    Map_tilePosToWorldPos(&pos.x, &pos.y, halfwayTile->x, halfwayTile->y);
    Object_setPos(obj, pos);
    CollisionHandler_Create_Square_Collider(obj, (AEVec2) { TILE_SIZE, TILE_SIZE }, 0, CheckpointOnCollision);
    ObjectManager_addObj(obj);

    initPlayers();

    if (splitScreen)
        ObjectManager_addObj(Object_new(NULL, NULL, separatorDraw, NULL, NULL, "Separator"));

    AEVec2 timerPos;
    timerPos.x = (splitScreen ? AEGfxGetWinMinX() / 2.f : AEGfxGetWinMinX()) + 30.f;
    timerPos.y = AEGfxGetWinMaxY() - 80.f;
    Object *timer = Timer_new(0, TEXTURES.font, timerPos, (AEVec2) {23, 42}, 0);
    ObjectManager_addObj(timer);

	GameStartTimer_init();
}

static void initPlayers() {
    unsigned startTileX = Map_getStartX(), startTileY = Map_getStartY();
    Tile startTile = *Map_getTile(startTileX, startTileY);
    float direction = 0;
    AEVec2 p1Offset = (AEVec2) { 0, 0 }, p2Offset = (AEVec2) { 0, 0 };
    switch (startTile.to) {
    case SUp:
        direction = 0.5f * PI;
        p1Offset.x -= MP_PLAYER_OFFSET;
        p2Offset.x += MP_PLAYER_OFFSET;
        break;
    case SDown:
        direction = 1.5f * PI;
        p1Offset.x += MP_PLAYER_OFFSET;
        p2Offset.x -= MP_PLAYER_OFFSET;
        break;
    case SLeft:
        direction = 1.f * PI;
        p1Offset.y -= MP_PLAYER_OFFSET;
        p2Offset.y += MP_PLAYER_OFFSET;
        break;
    case SRight:
        direction = 0.f * PI;
        p1Offset.y += MP_PLAYER_OFFSET;
        p2Offset.y -= MP_PLAYER_OFFSET;
        break;
    }

    AEVec2 pos1;
    Map_tilePosToWorldPos(&pos1.x, &pos1.y, startTileX, startTileY);
    if (splitScreen)
        AEVec2Add(&pos1, &pos1, &p1Offset);

    player1Lap = 1.f;
    AEVec2 lapPos1;
    lapPos1.x = (splitScreen ? AEGfxGetWinMinX() / 2.f : AEGfxGetWinMinX()) + 40.f;
    lapPos1.y = AEGfxGetWinMaxY() - 40.f;
	Object *lapCounter1 = LapCounter_new(0, "Lap %d", TEXTURES.font, lapPos1, (AEVec2) { 23, 42 }, &player1Lap);
	ObjectManager_addObj(lapCounter1);

    Object *player = Player_new(pos1, direction, (Controls) { 'A', 'D', 'W', 'S', 0 }, 0, &player1Lap);
    ObjectManager_addObj(player);
    CollisionHandler_Create_Circle_Collider(player, fmaxf(PLAYER_SCALE.x, PLAYER_SCALE.y) / 2, 0, PlayerOnCollision);
    Player1 = player;

	if (splitScreen) {
        Player_changeTexture(player, PLAYER_RED_TEXTURE);
		AEVec2 pos2;
		Map_tilePosToWorldPos(&pos2.x, &pos2.y, startTileX, startTileY);
        AEVec2Add(&pos2, &pos2, &p2Offset);

        player2Lap = 1.f;
        AEVec2 lapPos2;
        lapPos2.x = (splitScreen ? AEGfxGetWinMinX() / 2.f : AEGfxGetWinMinX()) + 40.f;
        lapPos2.y = AEGfxGetWinMaxY() - 40.f;
		Object *lapCounter2 = LapCounter_new(1, "Lap %d", TEXTURES.font, lapPos2, (AEVec2) { 23, 42 }, &player2Lap);

		ObjectManager_addObj(lapCounter2);

        player = Player_new(pos2, direction, (Controls) { VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 1 }, 1, &player2Lap);
        ObjectManager_addObj(player);
        Player_changeTexture(player, PLAYER_GREEN_TEXTURE);
        CollisionHandler_Create_Circle_Collider(player, fmaxf(PLAYER_SCALE.x, PLAYER_SCALE.y) / 2, 0, PlayerOnCollision);
        Player2 = player;
	}
}

void Level2_onUpdate(float dt)
{
    UNREFERENCED_PARAMETER(dt);

    Camera *cam = Camera_getCurr();
    if (AEInputCheckCurr('Q'))
        cam->worldScale *= 0.9f;
    if (AEInputCheckCurr('E'))
        cam->worldScale *= 1.1f;
	
	if (AEInputCheckCurr('R'))
		LevelManager_setNextLevel(EndScreen);

    if (AEInputCheckTriggered('O'))
    {
        s32 mX, mY;
        AEInputGetCursorPosition(&mX, &mY);
        float wX, wY;
        AEGfxConvertScreenCoordinatesToWorld((float)mX, (float)mY, &wX, &wY);
        AEVec2 loc;
        loc.x = wX;
        loc.y = wY;
        AEVec2 pos = Camera_applyInverse(Camera_getCurr(), loc);
        ObjectManager_addObj(Polarbear_new(pos));
    }

    if (splitScreen) {
        PlayerData *p1Data = (PlayerData*)Object_getData(Player1);
        PlayerData *p2Data = (PlayerData*)Object_getData(Player2);

        unsigned tileX, tileY;
        Map_worldPosToTilePos(&tileX, &tileY, Object_getPos(Player1).x, Object_getPos(Player1).y);
        unsigned p1Tile = Map_getTile(tileX, tileY)->tileNum + ((unsigned)floor(*p1Data->lap) * Map_NumTiles());
        Map_worldPosToTilePos(&tileX, &tileY, Object_getPos(Player2).x, Object_getPos(Player2).y);
        unsigned p2Tile = Map_getTile(tileX, tileY)->tileNum + ((unsigned)floor(*p2Data->lap) * Map_NumTiles());

        if (AEInputCheckTriggered('F')) {
            p1Data->speedScalar = p1Data->speedScalar;
        }
        int distance = abs((int)p1Tile - (int)p2Tile);
        if (p1Tile < p2Tile) {
            p1Data->speedScalar = 1.f + fminf(0.5, distance / 10.f);
            p2Data->speedScalar = 1.f;

            if (distance >= 8) CollisionHandler_SetPhaseDuration(Player1, 1);
        }
        else if (p2Tile < p1Tile) {
            p2Data->speedScalar = 1.f + fminf(0.5, distance / 10.f);
            p1Data->speedScalar = 1.f;

            if (distance >= 8) CollisionHandler_SetPhaseDuration(Player2, 1);
        }
    }

    if (AEInputCheckTriggered('P'))
    {
      Audio_playSfxGo();
    }
}

void Level2_onDraw()
{
    Background_onDraw();
    Map_draw();
}

static void separatorDraw(Object *obj, void *data) {
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
    Camera *cam = Camera_getCurr();
    float xPos = cam->viewportSize.x / 2.f - SCREEN_SEPARATOR_WIDTH / 2.f;
    AEVec2 pos;
    pos.x = (Camera_getCurrNum() == 0 ? xPos : -xPos);
    pos.y = 0;
    ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.screen_separator, pos, SCREEN_SEPARATOR_WIDTH, AEGfxGetWinSizeY(), 0, 1.0f);
}

void Level2_onShutdown()
{
    AEInputShowCursor(1);
	Camera_clear();
	Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, AEGfxGetWinSize());
}

void Level2_onUnload()
{
    Audio_stopGameplay();
}
