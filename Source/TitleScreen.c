/**
 * @file TitleScreen.c
 * @author Parker Friedland
 * @date 1/23/2019
 * @brief TitleScreen
 */

#include "stdafx.h"
#include "TitleScreen.h"
#include "ImageHandler.h"
#include "TextHandler.h"
#include "MeshHandler.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "Level2.h"
#include "Button.h"
#include "Background.h"

static void singleplayerButtonEffect() 
{
	splitScreen = 0;
	LevelManager_setNextLevel(Level2);
	
}

static void multiplayerButtonEffect() 
{
	splitScreen = 1;
	LevelManager_setNextLevel(Level2);
}

static void leaderboardEffect()
{
	LevelManager_setNextLevel(HighscoreScreen);
}

static void levelEditorEffect() 
{
	LevelManager_setNextLevel(LevelEditor);
}

static void quitEffect() 
{
	LevelManager_setNextLevel(LevelQuit);
}

static void titleDraw(Object *obj, void *data) 
{
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
	ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.titleScreen_title, (AEVec2) { 0, 250 }, 600, 100, 0, 1);
}

void TitleScreen_onLoad()
{
}

void TitleScreen_onInit()
{
    ObjectManager_addObj(Background_create());
	ObjectManager_addObj(Object_new(NULL, NULL, titleDraw, NULL, NULL, "Title"));

	Object *singlePlayerButton = Button_new(singleplayerButtonEffect, TEXTURES.titleScreen_startButton, TEXTURES.titleScreen_startButtonHover, TEXTURES.titleScreen_startButton,
        0,  100, 600, 100);
	Object *multiPlayerButton = Button_new(multiplayerButtonEffect, TEXTURES.titleScreen_startMultiButton, TEXTURES.titleScreen_startMultiButtonHover, TEXTURES.titleScreen_startButton,
		0,    0, 600, 100);
	Object *leaderboardButton = Button_new(leaderboardEffect, TEXTURES.titleScreen_leaderboardButton, TEXTURES.titleScreen_leaderboardButtonHover, NULL,
		0, -100, 600, 100);
    Object *levelEditorButton = Button_new(levelEditorEffect, TEXTURES.titleScreen_levelEditorButton, TEXTURES.titleScreen_levelEditorButtonHover, NULL, 
        0, -200, 600, 100);
	Object *exitButton = Button_new(quitEffect, TEXTURES.titleScreen_exitButton, TEXTURES.titleScreen_exitButtonHover, TEXTURES.titleScreen_exitButton,
		0, -300, 600, 100);
	Object *settingsButton = Button_new(NULL, TEXTURES.titleScreen_button, TEXTURES.titleScreen_button, TEXTURES.titleScreen_startButton,
	 -375,  375, 50, 50);


    ObjectManager_addObj(singlePlayerButton);
    ObjectManager_addObj(multiPlayerButton);
	ObjectManager_addObj(leaderboardButton);
	ObjectManager_addObj(levelEditorButton);
    ObjectManager_addObj(exitButton);
    ObjectManager_addObj(settingsButton);
}

void TitleScreen_onUpdate(float dt)
{
    Background_onDraw();
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
