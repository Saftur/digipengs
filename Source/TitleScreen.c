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
#include "LevelManager.h"
#include "Level2.h"

#include "Button.h"

AEGfxVertexList* titleMesh;
AEGfxVertexList* longButtonMesh;
AEGfxVertexList* squareButtonMesh;

static void singleplayerButtonEffect() {
	splitScreen = 0;
	LevelManager_setNextLevel(Level2);
	
}

static void multiplayerButtonEffect() {
	splitScreen = 1;
	LevelManager_setNextLevel(Level2);
}

static void quitEffect() {
	LevelManager_setNextLevel(LevelQuit);
}

static void titleDraw(Object *obj, void *data) {
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
	ImageHandler_drawTexture(titleMesh, TEXTURES.titleScreen_title, (AEVec2) { 0, 150 }, 0);
}

void TitleScreen_onLoad()
{
}

void TitleScreen_onInit()
{
	titleMesh = MeshHandler_createSquareMesh(600, 100);
	longButtonMesh = MeshHandler_createSquareMesh(600, 50);
	squareButtonMesh = MeshHandler_createSquareMesh(50, 50);

    ObjectManager_addObj(Object_new(NULL, NULL, titleDraw, NULL, NULL));

	Object *singlePlayerButton = Button_new(singleplayerButtonEffect, TEXTURES.titleScreen_startButton, TEXTURES.buttonSelected, TEXTURES.titleScreen_startButton,
        longButtonMesh, 0, 0, 600, 50);
	Object *multiPlayerButton = Button_new(multiplayerButtonEffect, TEXTURES.titleScreen_startButton, TEXTURES.buttonSelected, TEXTURES.titleScreen_startButton,
		longButtonMesh, 0, -100, 600, 50);
	Object *exitButton = Button_new(quitEffect, TEXTURES.titleScreen_exitButton, TEXTURES.buttonSelected, TEXTURES.titleScreen_exitButton,
		longButtonMesh, 0, -200, 600, 50);
	Object *settingsButton = Button_new(NULL, TEXTURES.titleScreen_button, TEXTURES.buttonSelected, TEXTURES.titleScreen_startButton,
		squareButtonMesh, -375, 275, 600, 50);

    ObjectManager_addObj(singlePlayerButton);
    ObjectManager_addObj(multiPlayerButton);
    ObjectManager_addObj(exitButton);
    ObjectManager_addObj(settingsButton);
}

void TitleScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt); // don't think we need this for the title screen but it's here just in case
	
	//ImageHandler_drawTexture(titleMesh, TEXTURES.titleScreen_title, (AEVec2) { 0, 150 }, 0);

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
