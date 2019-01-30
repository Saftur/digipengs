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

AEGfxVertexList* titleMesh;
AEGfxVertexList* longButtonMesh;
AEGfxVertexList* squareButtonMesh;

void TitleScreen_onLoad()
{
}

void TitleScreen_onInit()
{
	titleMesh = MeshHandler_createSquareMesh(600, 100);
	longButtonMesh = MeshHandler_createSquareMesh(600, 50);
	squareButtonMesh = MeshHandler_createSquareMesh(50, 50);

	Object *singlePlayerButton = Button_new(TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton, 
        longButtonMesh, (AEVec2) { 0, 0 });
	Object *multiPlayerButton = Button_new(TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton,
		longButtonMesh, (AEVec2) { 0, -100 });
	Object *exitButton = Button_new(TEXTURES.titleScreen_exitButton, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton,
		longButtonMesh, (AEVec2) { 0, -200 });
	Object *settingsButton = Button_new(TEXTURES.titleScreen_button, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton,
		squareButtonMesh, (AEVec2) { 0, 275 });

    ObjectManager_addObj(singlePlayerButton);
    ObjectManager_addObj(multiPlayerButton);
    ObjectManager_addObj(exitButton);
    ObjectManager_addObj(settingsButton);
}

void TitleScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt); // don't think we need this for the title screen but it's here just in case
	
	//ImageHandler_drawTexture(titleMesh, TEXTURES.titleScreen_title, (AEVec2) { 0, 200 }, 0);

	//ImageHandler_drawTexture(StartMesh, TEXTURES.titleScreen_startButton, (AEVec2) { 0, 0 });
	//ImageHandler_drawTexture(StartMesh, TEXTURES.titleScreen_startButton, (AEVec2) { 0, -100});
	//ImageHandler_drawTexture(ExitMesh, TEXTURES.titleScreen_exitButton, (AEVec2) { 0, -200 });
	//ImageHandler_drawTexture(OptionsMesh, TEXTURES.titleScreen_button, (AEVec2) { -375, 275 });
}

void TitleScreen_onShutdown()
{
}

void TitleScreen_onUnload()
{
}
