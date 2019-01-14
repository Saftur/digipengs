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

void LevelManagerInit()
{
    level.current = LevelInvalid;
    level.previous = LevelInvalid;
    level.next = InitialLevel;
}

static int LevelIsChanging();

void LevelManagerUpdate(float dt)
{
    if (LevelIsChanging()) {
        ExecuteLevelShutdown(level.current);

        if (!LevelManagerIsRestarting()) ExecuteLevelUnload(level.current);

        level.previous = level.current;
        level.current = level.next;

        if (!LevelManagerIsRestarting()) ExecuteLevelLoad(level.current);
        else {
            level.current = level.previous;
            level.next = level.current;
        }

        ExecuteLevelInit(level.current);
    }

    ExecuteLevelUpdate(level.current, dt);
}

void LevelManagerShutdown()
{
}

int LevelManagerIsRestarting()
{
    return level.next == LevelRestart;
}

int LevelManagerIsRunning()
{
    return level.current != LevelQuit;
}

void LevelManagerSetNextLevel(Levels nextLevel)
{
    if (LevelIsValid(nextLevel) || LevelIsSpecial(nextLevel)) {
        level.next = nextLevel;
    }
}

static int LevelIsChanging() {
    return level.current != level.next;
}
