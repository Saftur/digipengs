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
#include "Background.h"
#include "AudioHandler.h"
#include <AEExport.h>

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
	AEInputShowCursor(1);
	ObjectManager_addObj(Background_create());

	Object* musicVolumeLabel = Text_new("Music Volume:", TEXTURES.font, (AEVec2) {-250, 250}, 23, 42, (Color) { 1, 1, 1, 1 }, 0);

	Object* musicVolumeSlider = DragButton_new(&musicVolume, 0, 1, 
		TEXTURES.buttonSelected, TEXTURES.optionsScreen_track,
		TEXTURES.optionsScreen_track, TEXTURES.optionsScreen_track,
		0, 150, 0, 500, 50, 95, 95, 100, 100, 2.0f, 1.0f, 0);

	Object* SFXVolumeLabel = Text_new("Sound Effects Volume:", TEXTURES.font, (AEVec2) { -250, 0 }, 23, 42, (Color) { 1, 1, 1, 1 }, 0);

	Object* SFXVolumeSlider = DragButton_new(&SFXVolume, 0, 1,
		TEXTURES.buttonSelected, TEXTURES.optionsScreen_track,
		TEXTURES.optionsScreen_track, TEXTURES.optionsScreen_track,
		0, -100, 0, 500, 50, 95, 95, 100, 100, 2.0f, 1.0f, 0);

	titleScreenButton = Button_new(titleScreenEffect, 
		TEXTURES.endScreen_titleScreenButton, TEXTURES.buttonSelected, TEXTURES.endScreen_titleScreenButton,
		0, -250, 500, 80, 600, 100, 2.0f, 1.0f, 0);

	ObjectManager_addObj(musicVolumeLabel);
	ObjectManager_addObj(musicVolumeSlider);
	ObjectManager_addObj(SFXVolumeSlider);
	ObjectManager_addObj(SFXVolumeLabel);
	ObjectManager_addObj(titleScreenButton);
}

void OptionsScreen_onUpdate(float dt)
{
	Background_onDraw();
	UNREFERENCED_PARAMETER(dt);
}

void OptionsScreen_onShutdown()
{
}

void OptionsScreen_onUnload()
{
}
