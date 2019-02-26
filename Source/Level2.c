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
#include "ObstacleManager.h"

int splitScreen = 0;

void Level2_onLoad()
{
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
    Map_tilePosToWorldPos(&pos1.x, &pos1.y, 1, 2);
    pos1.y += 32;
    Object *player = Player_new(pos1, (Controls) { 'A', 'D', 'W', 'S', 0 }, 0);
    ObjectManager_addObj(player);
    CollisionHandler_Create_Circle_Collider(player, fmaxf(PLAYER_SCALE.x, PLAYER_SCALE.y) / 2, PlayerOnCollision);

	if (splitScreen) {
		AEVec2 pos2;
		Map_tilePosToWorldPos(&pos2.x, &pos2.y, 1, 2);
        pos2.y -= 32;
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

    if (cam) Map_draw();
}

void Level2_onShutdown()
{
	if (splitScreen) {
		Camera_clear();
		Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, (AEVec2) { 800, 600 });
	}
}

void Level2_onUnload()
{
}
