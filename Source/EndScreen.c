/**
 * @file EndScreen.h
 * @author Arthur Bouvier
 * @date 3/10/2019
 * @brief End screen implementation
 */

#include "stdafx.h"
#include "EndScreen.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "ObjectManager.h"
#include "LevelManager.h"

#include "Button.h"

AEGfxVertexList* youDiedMesh;
AEGfxVertexList* buttonMesh;

int EndScreen_winner = 0;

static void tryAgainEffect() {
	LevelManager_setNextLevel(Level2);
}

static void titleScreenEffect() {
	LevelManager_setNextLevel(TitleScreen);
}

static void quitEffect() {
	LevelManager_setNextLevel(LevelQuit);
}


void EndScreen_onLoad()
{
}

void EndScreen_onInit()
{
	Object *tryAgainButton = Button_new(tryAgainEffect, TEXTURES.endScreen_tryAgainButton, TEXTURES.buttonSelected, TEXTURES.endScreen_tryAgainButton,
		0, 0, 600, 100, 0);
	Object *mainMenuButton = Button_new(titleScreenEffect, TEXTURES.endScreen_titleScreenButton, TEXTURES.buttonSelected, TEXTURES.endScreen_titleScreenButton,
		0, -100, 600, 100, 0);
	Object *exitButton = Button_new(quitEffect, TEXTURES.titleScreen_exitButton, TEXTURES.buttonSelected, TEXTURES.titleScreen_exitButton,
		0, -200, 600, 100, 0);

	ObjectManager_addObj(tryAgainButton);
	ObjectManager_addObj(mainMenuButton);
	ObjectManager_addObj(exitButton);
}

void EndScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void EndScreen_onDraw() {
    AEGfxTexture *topTexture = NULL;

    switch (EndScreen_winner) {
    case 1:
        topTexture = TEXTURES.endScreen_player1Wins;
        break;
    case 2:
        topTexture = TEXTURES.endScreen_player2Wins;
        break;
    }

    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), topTexture, (AEVec2) { 0, 150 }, 600, 100, 0, 1);
}

void EndScreen_onShutdown()
{
}

void EndScreen_onUnload()
{
}
