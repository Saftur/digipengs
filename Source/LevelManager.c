/**
 * @file LevelManager.c
 * @author Brand Knutson
 * @date 1/10/2019
 * @brief Handle loading and switching levels.
 */

#include "stdafx.h"
#include "LevelManager.h"

typedef struct {
    Levels current;
    Levels previous;
    Levels next;
} Level;

static Level level;

void LevelManager_init()
{
    level.current = LevelInvalid;
    level.previous = LevelInvalid;
    level.next = InitialLevel;
}

static int LevelIsChanging();

void LevelManager_update(float dt)
{
    if (LevelIsChanging()) {
        ExecuteLevelShutdown(level.current);

        if (!LevelManager_isRestarting()) ExecuteLevelUnload(level.current);

        level.previous = level.current;
        level.current = level.next;

        if (!LevelManager_isRestarting()) ExecuteLevelLoad(level.current);
        else {
            level.current = level.previous;
            level.next = level.current;
        }

        ExecuteLevelInit(level.current);
    }

    ExecuteLevelUpdate(level.current, dt);
}

void LevelManager_shutdown()
{
}

int LevelManager_isRestarting()
{
    return level.next == LevelRestart;
}

int LevelManager_isRunning()
{
    return level.current != LevelQuit;
}

void LevelManager_setNextLevel(Levels nextLevel)
{
    if (LevelIsValid(nextLevel) || LevelIsSpecial(nextLevel)) {
        level.next = nextLevel;
    }
}

static int LevelIsChanging() {
    return level.current != level.next;
}
