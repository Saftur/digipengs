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

void HighscoreScreen_onLoad()
{
}

void HighscoreScreen_onInit()
{
	Default_Leaderboard(0);
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
