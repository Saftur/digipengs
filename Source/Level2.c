/**
 * @file Level2.c
 * @author Richard Folorunso
 * @date 1/30/2019
 * @brief Test Level
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

#define SCREEN_SEPARATOR_WIDTH 10

#define MP_PLAYER_OFFSET 64

int splitScreen = 0;

static AEGfxVertexList *separatorMesh;

static void initPlayers();
static void separatorDraw(Object *obj, void *data);

void Level2_onLoad()
{
    separatorMesh = MeshHandler_createSquareMesh(SCREEN_SEPARATOR_WIDTH, AEGfxGetWinSizeY(), 1, 1);
    //Audio_playGameplay();
}

void Level2_onInit()
{
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

    Tile tile = Map_getStartTile();
    Tile halfwayTile = tile;

    do {
        tile = Map_getNextTile(tile);
        if (tile.isStart)
            break;
        tile = Map_getNextTile(tile);
        halfwayTile = Map_getNextTile(halfwayTile);
    } while (!tile.isStart);

    Object *obj;
    AEVec2 pos;

    obj = Object_new(NULL, NULL, NULL, NULL, NULL, "Start");
    Map_tilePosToWorldPos(&pos.x, &pos.y, Map_getStartX(), Map_getStartY());
    AEVec2 size = (AEVec2) { 0.f, 0.f };
    if (tile.to == SLeft) {
        pos.x -= LANE_WIDTH;
        size = (AEVec2) { LANE_WIDTH * 2, TILE_SIZE };
    } else if (tile.to == SRight) {
        pos.x += LANE_WIDTH;
        size = (AEVec2) { LANE_WIDTH * 2, TILE_SIZE };
    } else if (tile.to == SUp) {
        pos.y += LANE_WIDTH;
        size = (AEVec2) { TILE_SIZE, LANE_WIDTH * 2 };
    } else if (tile.to == SDown) {
        pos.y -= LANE_WIDTH;
        size = (AEVec2) { TILE_SIZE, LANE_WIDTH * 2 };
    }
    Object_setPos(obj, pos);
    CollisionHandler_Create_Square_Collider(obj, size, 0, StartLineOnCollision);
    ObjectManager_addObj(obj);

    obj = Object_new(NULL, NULL, NULL, NULL, NULL, "Checkpoint");
    Map_tilePosToWorldPos(&pos.x, &pos.y, halfwayTile.x, halfwayTile.y);
    Object_setPos(obj, pos);
    CollisionHandler_Create_Square_Collider(obj, (AEVec2) { TILE_SIZE, TILE_SIZE }, 0, CheckpointOnCollision);
    ObjectManager_addObj(obj);

    initPlayers();

    if (splitScreen)
        ObjectManager_addObj(Object_new(NULL, NULL, separatorDraw, NULL, NULL, "Separator"));
}

static void initPlayers() {
    unsigned startTileX = Map_getStartX(), startTileY = Map_getStartY();
    Tile startTile = Map_getTile(startTileX, startTileY);
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
    Object *player = Player_new(pos1, direction, (Controls) { 'A', 'D', 'W', 'S', 0 }, 0);
    ObjectManager_addObj(player);
    CollisionHandler_Create_Circle_Collider(player, fmaxf(PLAYER_SCALE.x, PLAYER_SCALE.y) / 2, 0, PlayerOnCollision);

	if (splitScreen) {
        Player_changeTexture(player, PLAYER_RED_TEXTURE);
		AEVec2 pos2;
		Map_tilePosToWorldPos(&pos2.x, &pos2.y, startTileX, startTileY);
        AEVec2Add(&pos2, &pos2, &p2Offset);
        player = Player_new(pos2, direction, (Controls) { VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN }, 1);
        ObjectManager_addObj(player);
        Player_changeTexture(player, PLAYER_GREEN_TEXTURE);
        CollisionHandler_Create_Circle_Collider(player, fmaxf(PLAYER_SCALE.x, PLAYER_SCALE.y) / 2, 0, PlayerOnCollision);
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

}

void Level2_onDraw()
{
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
    ImageHandler_screenDrawTexture(separatorMesh, TEXTURES.screen_separator, pos, 1, 1, 0, 1.0f);
}

void Level2_onShutdown()
{
	Camera_clear();
	Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, AEGfxGetWinSize());
}

void Level2_onUnload()
{
    AEGfxMeshFree(separatorMesh);
    Audio_stopGameplay();
}
