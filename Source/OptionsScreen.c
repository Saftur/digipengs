/**
 * @file OptionsScreen.c
 * @author Parker Friedland
 * @date 4/3/2019
 * @brief Options Screen
 */

#include "stdafx.h"
#include "OptionsScreen.h"
#include "ImageHandler.h"
#include "TextHandler.h"
#include "MeshHandler.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "Level2.h"
#include "Button.h"
#include "DragButton.h"
#include <AEExport.h>

float test = 1;
Object* titleScreenButton;

static void titleScreenEffect()
{
	LevelManager_setNextLevel(TitleScreen);
}

void OptionsScreen_onLoad()
{
}

void OptionsScreen_onInit()
{
	Object* dragButton = DragButton_new(&test, 0, 1, 
		TEXTURES.buttonSelected, TEXTURES.titleScreen_levelEditorButton, TEXTURES.buttonSelected, TEXTURES.titleScreen_levelEditorButton,
		0, 0, PI / 4, 500, 50, 100, 100);

	titleScreenButton = Button_new(titleScreenEffect, 
		TEXTURES.endScreen_titleScreenButton, TEXTURES.buttonSelected, TEXTURES.endScreen_titleScreenButton,
		0, -300, 600, 100, 0);

	ObjectManager_addObj(titleScreenButton);
	ObjectManager_addObj(dragButton);
}

void OptionsScreen_onUpdate(float dt)
{
	AEVec2 pos = { 0, -300 };
	pos.x += 100*test;

	Object_setPos(titleScreenButton, pos);
	UNREFERENCED_PARAMETER(dt);
}

void OptionsScreen_onShutdown()
{
}

void OptionsScreen_onUnload()
{
}
