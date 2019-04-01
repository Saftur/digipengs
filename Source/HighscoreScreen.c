/**
 * @file HighscoreScreen.c
 * @author Parker Friedland
 * @date 3/31/2019
 * @brief HighScoreScreen
 */

#include "stdafx.h"
#include "HighscoreScreen.h"
#include "ImageHandler.h"
#include "Leaderboard.h"
#include "MeshHandler.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "TitleScreen.h"
#include "Button.h"

static void titleScreenEffect() {
	LevelManager_setNextLevel(TitleScreen);
}

void HighscoreScreen_onLoad()
{
}

void HighscoreScreen_onInit()
{
	Color palette[LEADERBOARD_PALETTE_ROWS][LEADERBOARD_PALETTE_COLUMNS] = {
			{ { 1, 1, 1, 1, }, { 1, 1, 1, 1, }, { 1, 1, 1, 1, } },
			{ { 1, 1, 1, 1, }, { 1, 1, 1, 1, }, { 1, 1, 1, 1, } },
			{ { 1, 1, 1, 1, }, { 1, 1, 1, 1, }, { 1, 1, 1, 1, } } };

	Object* leaderboard = Leaderboard_new(TEXTURES.font, (AEVec2) { -375, 275 }, (AEVec2) { 5, 45 }, (AEVec2) { 23, 42 }, palette, 0, 10, 0.2f);
	Object* titleScreenButton = Button_new(titleScreenEffect, TEXTURES.endScreen_titleScreenButton, TEXTURES.buttonSelected, TEXTURES.endScreen_titleScreenButton,
		0, -300, 600, 100);

	ObjectManager_addObj(leaderboard);
	ObjectManager_addObj(titleScreenButton);
}

void HighscoreScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void HighscoreScreen_onShutdown()
{
}

void HighscoreScreen_onUnload()
{
}