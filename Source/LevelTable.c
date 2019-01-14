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
    {Level1Load, Level1Init, Level1Update, Level1Shutdown, Level1Unload}
};

int LevelIsValid(Levels level)
{
    return ((level >= 0) && (level < LevelNum));
}

int LevelIsSpecial(Levels level)
{
    return level == LevelQuit || level == LevelRestart;
}

void ExecuteLevelLoad(Levels level)
{
    if (LevelIsValid(level) && (*LevelTable[level].levelLoad) != NULL) (*LevelTable[level].levelLoad)();
}

void ExecuteLevelInit(Levels level)
{
    if (LevelIsValid(level) && (*LevelTable[level].levelInit) != NULL) (*LevelTable[level].levelInit)();
}

void ExecuteLevelUpdate(Levels level, float dt)
{
    if (LevelIsValid(level) && ((*LevelTable[level].levelUpdate) != NULL)) (*LevelTable[level].levelUpdate)(dt);
}

void ExecuteLevelShutdown(Levels level)
{
    if (LevelIsValid(level) && ((*LevelTable[level].levelShutdown) != NULL)) (*LevelTable[level].levelShutdown)();
}

void ExecuteLevelUnload(Levels level)
{
    if (LevelIsValid(level) && ((*LevelTable[level].levelUnload) != NULL)) (*LevelTable[level].levelUnload)();
}
