/**
 * Project: DigitalPenguins
 * All content � 2019 DigiPen (USA) Corporation, all rights reserved.
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
#include "Background.h"

void HighscoreScreen_onLoad()
{
}

void HighscoreScreen_onInit()
{
	AEInputShowCursor(1);
	ObjectManager_addObj(Background_create());
	Default_Leaderboard(0, 0);
}

void HighscoreScreen_onUpdate(float dt)
{
	Background_onDraw();
	UNREFERENCED_PARAMETER(dt);
}

void HighscoreScreen_onShutdown()
{
}

void HighscoreScreen_onUnload()
{
}
