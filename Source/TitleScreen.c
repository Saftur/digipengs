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
AEGfxVertexList* LongButtonMesh;
AEGfxVertexList* SquareButtonMesh;

void TitleScreen_onLoad()
{
}

void TitleScreen_onInit()
{
	TitleMesh = MeshHandler_createSquareMesh(600, 100);
	LongButtonMesh = MeshHandler_createSquareMesh(600, 50);
	SquareButtonMesh = MeshHandler_createSquareMesh(50, 50);

	Object *singlePlayerButton = Button_new(TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton, 
		LongButtonMesh, 0, 0);
	Object *multiPlayerButton = Button_new(TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton,
		LongButtonMesh, 0, -100);
	Object *exitButton = Button_new(TEXTURES.titleScreen_exitButton, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton,
		LongButtonMesh, 0, -200);
	Object *settingsButton = Button_new(TEXTURES.titleScreen_button, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButton,
		SquareButtonMesh, 0, 275);
}

void TitleScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt); // don't think we need this for the title screen but it's here just in case
	
	ImageHandler_drawTexture(TitleMesh, TEXTURES.titleScreen_title, (AEVec2) { 0, 200 });

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
