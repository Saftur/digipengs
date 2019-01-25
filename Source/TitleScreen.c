/**
 * @file Level1.c
 * @author Parker Friedland
 * @date 1/23/2019
 * @brief TitleScreen
 */

#include "stdafx.h"
#include "TitleScreen.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "ObjectManager.h"

#include "Button.h"

AEGfxVertexList* TitleMesh;
AEGfxVertexList* StartMesh;
AEGfxVertexList* OptionsMesh;
AEGfxVertexList* ExitMesh;

void TitleScreen_onLoad()
{
}

void TitleScreen_onInit()
{
	TitleMesh = MeshHandler_createSquareMesh(600, 100);
	StartMesh = MeshHandler_createSquareMesh(600, 50);
	OptionsMesh = MeshHandler_createSquareMesh(50, 50);
	ExitMesh = MeshHandler_createSquareMesh(600, 50);

	Object *startButton = Button_new(TEXTURES.titleScreen_startButton, StartMesh);
	Object_setPos(startButton, (AEVec2) { 0, 0 });
	ObjectManager_addObj(startButton);
}

void TitleScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt); // don't think we need this for the title screen but it's here just in case
	
	ImageHandler_drawTexture(TitleMesh, TEXTURES.titleScreen_title, (AEVec2) { 0, 200 });
	ImageHandler_drawTexture(StartMesh, TEXTURES.titleScreen_startButton, (AEVec2) { 0, 0 });
	ImageHandler_drawTexture(StartMesh, TEXTURES.titleScreen_startButton, (AEVec2) { 0, -100});
	ImageHandler_drawTexture(ExitMesh, TEXTURES.titleScreen_exitButton, (AEVec2) { 0, -200 });

	ImageHandler_drawTexture(OptionsMesh, TEXTURES.titleScreen_button, (AEVec2) { -375, 275 });
}

void TitleScreen_onShutdown()
{
}

void TitleScreen_onUnload()
{
}
