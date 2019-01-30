/**
 * @file LevelTable.c
 * @author Brand Knutson
 * @date 1/10/2019
 * @brief List of all levels.
 */

#include "stdafx.h"
#include "LevelTable.h"

//Levels
#include "Level1.h"
#include "TitleScreen.h"

 /**
  * @struct TableEntry
  * @brief function pointers for entries to LevelTable
  */
typedef struct {
    void(*levelLoad)();             ///< Pointer to level load function.
    void(*levelInit)();             ///< Pointer to level init function.
    void(*levelUpdate)(float dt);   ///< Pointer to level update function.
    void(*levelShutdown)();         ///< Pointer to level shutdown function.
    void(*levelUnload)();           ///< Pointer to level unload function.
} TableEntry;

///< Table of all levels and functions for said levels.
static const TableEntry LevelTable[LevelNum] = {
    {Level1_onLoad, Level1_onInit, Level1_onUpdate, Level1_onShutdown, Level1_onUnload},
	{TitleScreen_onLoad, TitleScreen_onInit, TitleScreen_onUpdate, TitleScreen_onShutdown, TitleScreen_onUnload}
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

void Level_shutdown(Levels level)
{
    if (Level_isValid(level) && ((*LevelTable[level].levelShutdown) != NULL)) (*LevelTable[level].levelShutdown)();
}

void Level_unload(Levels level)
{
    if (Level_isValid(level) && ((*LevelTable[level].levelUnload) != NULL)) (*LevelTable[level].levelUnload)();
}
