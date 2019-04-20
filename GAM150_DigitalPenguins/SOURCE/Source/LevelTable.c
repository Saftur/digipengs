/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelTable.c
 * @author Brand Knutson
 * @date 1/10/2019
 * @brief List of all levels.
 */

#include "stdafx.h"
#include "LevelTable.h"

//Levels
#include "Level1.h"
#include "Level2.h"
#include "SplashScreen.h"
#include "TitleScreen.h"
#include "HighscoreScreen.h"
#include "OptionsScreen.h"
#include "EndScreen.h"
#include "LevelEditorLevel.h"
#include "LevelCredits1.h"
#include "LevelCredits2.h"
#include "LevelCredits3.h"
#include "LevelCredits4.h"
#include "LevelCredits5.h"

 /**
  * @struct TableEntry
  * @brief function pointers for entries to LevelTable
  */
typedef struct {
    void(*levelLoad)();             ///< Pointer to level load function.
    void(*levelInit)();             ///< Pointer to level init function.
    void(*levelUpdate)(float dt);   ///< Pointer to level update function.
    void(*levelDraw)();             ///< Pointer to level draw function.
    void(*levelShutdown)();         ///< Pointer to level shutdown function.
    void(*levelUnload)();           ///< Pointer to level unload function.
} TableEntry;

///< Table of all levels and functions for said levels.
static const TableEntry LevelTable[LevelNum] = {
    {Level1_onLoad, Level1_onInit, Level1_onUpdate, NULL, Level1_onShutdown, Level1_onUnload},
	{Level2_onLoad, Level2_onInit, Level2_onUpdate, Level2_onDraw, Level2_onShutdown, Level2_onUnload},
    {SplashScreen_onLoad, SplashScreen_onInit, SplashScreen_onUpdate, NULL, SplashScreen_onShutdown, SplashScreen_onUnload},
	{TitleScreen_onLoad, TitleScreen_onInit, TitleScreen_onUpdate, NULL, TitleScreen_onShutdown, TitleScreen_onUnload},
	{HighscoreScreen_onLoad, HighscoreScreen_onInit, HighscoreScreen_onUpdate, NULL, HighscoreScreen_onShutdown, HighscoreScreen_onUnload},
	{OptionsScreen_onLoad, OptionsScreen_onInit, OptionsScreen_onUpdate, NULL, OptionsScreen_onShutdown, OptionsScreen_onUnload},
	{EndScreen_onLoad, EndScreen_onInit, EndScreen_onUpdate, EndScreen_onDraw, EndScreen_onShutdown, EndScreen_onUnload},
    {LevelEditorLevel_onLoad, LevelEditorLevel_onInit, LevelEditorLevel_onUpdate, NULL, LevelEditorLevel_onShutdown, LevelEditorLevel_onUnload},
    {LevelCredits1_onLoad, LevelCredits1_onInit, LevelCredits1_onUpdate, NULL, LevelCredits1_onShutdown, LevelCredits1_onUnload},
    {LevelCredits2_onLoad, LevelCredits2_onInit, LevelCredits2_onUpdate, NULL, LevelCredits2_onShutdown, LevelCredits2_onUnload},
    {LevelCredits3_onLoad, LevelCredits3_onInit, LevelCredits3_onUpdate, NULL, LevelCredits3_onShutdown, LevelCredits3_onUnload},
    {LevelCredits4_onLoad, LevelCredits4_onInit, LevelCredits4_onUpdate, NULL, LevelCredits4_onShutdown, LevelCredits4_onUnload},
    {LevelCredits5_onLoad, LevelCredits5_onInit, LevelCredits5_onUpdate, NULL, LevelCredits5_onShutdown, LevelCredits5_onUnload}
};

int Level_isValid(Levels level)
{
    return ((level >= 0) && (level < LevelNum));
}

int Level_isSpecial(Levels level)
{
    return level == LevelQuit || level == LevelRestart;
}

void Level_load(Levels level)
{
    if (Level_isValid(level) && (*LevelTable[level].levelLoad) != NULL) (*LevelTable[level].levelLoad)();
}

void Level_init(Levels level)
{
    if (Level_isValid(level) && (*LevelTable[level].levelInit) != NULL) (*LevelTable[level].levelInit)();
}

void Level_update(Levels level, float dt)
{
    if (Level_isValid(level) && ((*LevelTable[level].levelUpdate) != NULL)) (*LevelTable[level].levelUpdate)(dt);
}

void Level_draw(Levels level) {
    if (Level_isValid(level) && ((*LevelTable[level].levelDraw) != NULL)) (*LevelTable[level].levelDraw)();
}

void Level_shutdown(Levels level)
{
    if (Level_isValid(level) && ((*LevelTable[level].levelShutdown) != NULL)) (*LevelTable[level].levelShutdown)();
}

void Level_unload(Levels level)
{
    if (Level_isValid(level) && ((*LevelTable[level].levelUnload) != NULL)) (*LevelTable[level].levelUnload)();
}
