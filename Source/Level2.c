/**
 * @file Level2.c
 * @author Richard Folorunso
 * @date 1/30/2019
 * @brief Test Level
 */

#include "stdafx.h"
#include "AEEngine.h"
#include "Level2.h"
#include "ObjectManager.h"
#include "Button.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Player.h"
#include "Object.h"
#include "Map.h"
#include "ObstacleManager.h"

#include "Camera.h"

static AEGfxVertexList* mapMesh;

static void mapDraw(Object *obj, void *data) {
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
    ImageHandler_drawTexture(mapMesh, TEXTURES.map, (AEVec2) { 512, -512 }, 0);
}

void Level2_onLoad()
{
}

void Level2_onInit()
{
    Camera_clear();
    Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, (AEVec2) { 400, 600 });
    Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 400, 0 }, (AEVec2) { 400, 600 });

	mapMesh = MeshHandler_createSquareMesh(1050, 1050);
	// Map Texture: From file
	//ObjectManager_addObj(Button_new(TEXTURES.map, mapMesh, (AEVec2) { 512, -512 }));
    ObjectManager_addObj(Object_new(NULL, NULL, mapDraw, NULL, NULL));

    Map_init("Assets\\Map.txt");

    AEVec2 pos1;
    Map_tilePosToWorldPos(&pos1.x, &pos1.y, 1, 2);
    pos1.y += 32;
    ObjectManager_addObj(Player_new(pos1, (Controls) {'A', 'D', 'W', 'S'}, 0));
    AEVec2 pos2;
    Map_tilePosToWorldPos(&pos2.x, &pos2.y, 1, 2);
    pos2.y -= 32;
	ObjectManager_addObj(Player_new(pos2, (Controls) {VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN}, 1));

    ObstacleManager_generateObstacles((AEVec2) { 0, 0 });
}

void Level2_onUpdate(float dt)
{
    UNREFERENCED_PARAMETER(dt);
    
    Camera *cam = Camera_getCurr();
    if (AEInputCheckCurr('Q'))
        cam->worldScale *= 0.9f;
    if (AEInputCheckCurr('E'))
        cam->worldScale *= 1.1f;
}

void Level2_onShutdown()
{
    AEGfxMeshFree(mapMesh);
    Camera_clear();
    Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, (AEVec2) { 800, 600 });
}

void Level2_onUnload()
{
}
