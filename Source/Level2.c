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


void Level2_onLoad()
{
}

void Level2_onInit()
{
	AEGfxVertexList* mapMesh;
	mapMesh = MeshHandler_createSquareMesh(1024, 1024);
	// Map Texture: From file
	ObjectManager_addObj(Button_new(TEXTURES.map, mapMesh, (AEVec2) { 512, -512 }));

    Map_init("Assets\\Map.txt");

    AEVec2 pos1;
    Map_tilePosToWorldPos(&pos1.x, &pos1.y, 1, 2);
    ObjectManager_addObj(Player_new(pos1, (Controls) {'A', 'D', 'W', 'S'}, 0));
    pos1.y += 32;
    AEVec2 pos2;
    Map_tilePosToWorldPos(&pos2.x, &pos2.y, 1, 2);
    pos2.y -= 32;
	ObjectManager_addObj(Player_new(pos2, (Controls) {VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN}, 1));
}

void Level2_onUpdate(float dt)
{
    UNREFERENCED_PARAMETER(dt);

	//Player_onUpdate(Player, Object_getData(Player), dt);
	
	/*AEGfxVertexList     *pMeshMap;	// Pointer to Map Mesh
	AEGfxTexture        *pTexMap;	// Pointer to Map Texture

	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
		30.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
		-30.0f, 30.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		300.0f, -300.0f, 0x00FFFFFF, 1.0f, 1.0f,
		300.0f, 300.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-300.0f, 300.0f, 0x00FFFFFF, 0.0f, 0.0f);

	pMeshMap = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshMap, "Failed to create Map mesh!");


	// Map Texture: From file
	pTexMap = AEGfxTextureLoad("./Assets/Map.png");
	AE_ASSERT_MESG(pTexMap, "Failed to create Map texture!!");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxTextureSet(pTexMap, 0.0f, 0.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(pMeshMap, AE_GFX_MDM_TRIANGLES);
	AESysFrameEnd();*/
}

void Level2_onShutdown()
{
	//EGfxMeshFree(pMeshMap);
	//AEGfxTextureUnload(pTexMap);
}

void Level2_onUnload()
{
}
