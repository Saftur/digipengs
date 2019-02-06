/**
 * @file Level1.c
 * @author Parker Friedland
 * @date 1/23/2019
 * @brief TitleScreen
 */

#include "stdafx.h"
#include "EndScreen.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "ObjectManager.h"

#include "Button.h"

AEGfxVertexList* youDiedMesh;
AEGfxVertexList* buttonMesh;

void EndScreen_onLoad()
{
}

void EndScreen_onInit()
{
	youDiedMesh = MeshHandler_createSquareMesh(600, 100);
	buttonMesh = MeshHandler_createSquareMesh(600, 50);

	ObjectManager_addObj(Button_new(TEXTURES.endScreen_tryAgainButton, buttonMesh, (AEVec2) { 0, 0 }));
	ObjectManager_addObj(Button_new(TEXTURES.endScreen_mainMenuButton, buttonMesh, (AEVec2) { 0, -100 }));
	ObjectManager_addObj(Button_new(TEXTURES.titleScreen_exitButton, buttonMesh, (AEVec2) { 0, -200 }));
}

void EndScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt); // don't think we need this for the title screen but it's here just in case

	//ImageHandler_drawTexture(TitleMesh, TEXTURES.titleScreen_title, (AEVec2) { 0, 200 });
	//ImageHandler_drawTexture(StartMesh, TEXTURES.titleScreen_startButton, (AEVec2) { 0, 0 });
	//ImageHandler_drawTexture(StartMesh, TEXTURES.titleScreen_startButton, (AEVec2) { 0, -100});
	//ImageHandler_drawTexture(ExitMesh, TEXTURES.titleScreen_exitButton, (AEVec2) { 0, -200 });

	//ImageHandler_drawTexture(OptionsMesh, TEXTURES.titleScreen_button, (AEVec2) { -375, 275 });
}

void EndScreen_onShutdown()
{
}

void EndScreen_onUnload()
{
}