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
#include "Camera.h"
#include "Polarbear.h"
#include "ObstacleManager.h"

#define SCREEN_SEPARATOR_WIDTH 10

int splitScreen = 0;

static AEGfxVertexList *separatorMesh;

void Level2_onLoad()
{
    separatorMesh = MeshHandler_createSquareMesh(SCREEN_SEPARATOR_WIDTH, AEGfxGetWinMaxY() - AEGfxGetWinMinY());
}

void Level2_onInit()
{
	if (splitScreen)
	{
		Camera_clear();
		Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, (AEVec2) { 400, 600 });
		Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 400, 0 }, (AEVec2) { 400, 600 });
	}

    Map_init("Assets\\Map.txt");
    ObstacleManager_loadObstacles();

    AEVec2 pos1;
    Map_tilePosToWorldPos(&pos1.x, &pos1.y, 0, 0);
    pos1.x += 32;
    Object *player = Player_new(pos1, (Controls) { 'A', 'D', 'W', 'S', 0 }, 0);
    ObjectManager_addObj(player);
    CollisionHandler_Create_Circle_Collider(player, fmaxf(PLAYER_SCALE.x, PLAYER_SCALE.y) / 2, PlayerOnCollision);

	if (splitScreen) {
		AEVec2 pos2;
		Map_tilePosToWorldPos(&pos2.x, &pos2.y, 0, 0);
        pos2.x -= 32;
        player = Player_new(pos2, (Controls) { VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN }, 1);
		ObjectManager_addObj(player);
        CollisionHandler_Create_Circle_Collider(player, fmaxf(PLAYER_SCALE.x, PLAYER_SCALE.y) / 2, PlayerOnCollision);
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
    if (splitScreen) {
        Camera *cam = Camera_getCurr();
        float xPos = cam->viewportSize.x / 2.f - SCREEN_SEPARATOR_WIDTH / 2.f;
        AEVec2 pos;
        pos.x = (Camera_getCurrNum() == 0 ? xPos : -xPos);
        pos.y = 0;
        ImageHandler_screenDrawTexture(separatorMesh, TEXTURES.screen_separator, pos, 1, 0, 1.0f);
    }
}

void Level2_onShutdown()
{
	Camera_clear();
	Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, (AEVec2) { 800, 600 });
}

void Level2_onUnload()
{
    AEGfxMeshFree(separatorMesh);
}
