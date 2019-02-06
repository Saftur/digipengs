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
#include "LevelManager.h"

#include "Button.h"

AEGfxVertexList* youDiedMesh;
AEGfxVertexList* buttonMesh;

static void tryAgainEffect() {
	LevelManager_setNextLevel(Level1);
}

static void titleScreenEffect() {
	LevelManager_setNextLevel(TitleScreen);
}

void EndScreen_onLoad()
{
}

void EndScreen_onInit()
{
	youDiedMesh = MeshHandler_createSquareMesh(600, 100);
	buttonMesh = MeshHandler_createSquareMesh(600, 50);

	Object *tryAgainButton = Button_new(tryAgainEffect, TEXTURES.endScreen_tryAgainButton, TEXTURES.endScreen_tryAgainButton, TEXTURES.endScreen_tryAgainButton,
		buttonMesh, 0, 0, 600, 50);
	Object *mainMenuButton = Button_new(titleScreenEffect, TEXTURES.endScreen_titleScreenButton, TEXTURES.endScreen_titleScreenButton, TEXTURES.endScreen_titleScreenButton,
		buttonMesh, 0, -100, 600, 50);
	Object *exitButton = Button_new(NULL, TEXTURES.titleScreen_exitButton, TEXTURES.titleScreen_exitButton, TEXTURES.titleScreen_exitButton,
		buttonMesh, 0, -200, 600, 50);

	ObjectManager_addObj(tryAgainButton);
	ObjectManager_addObj(mainMenuButton);
	ObjectManager_addObj(exitButton);
}

void EndScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	ImageHandler_drawTexture(youDiedMesh, TEXTURES.endScreen_youDied, (AEVec2) { 0, 150 }, 0);
}

void EndScreen_onShutdown()
{
}

void EndScreen_onUnload()
{
}