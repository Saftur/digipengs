/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelManager.c
 * @author Brand Knutson
 * @date 1/10/2019
 * @brief Handle loading and switching levels.
 */

#include "stdafx.h"
#include "LevelManager.h"
#include "ObjectManager.h"

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
        Level_shutdown(level.current);
        ObjectManager_reset();

        if (!LevelManager_isRestarting()) Level_unload(level.current);

        level.previous = level.current;
        level.current = level.next;

        if (!LevelManager_isRestarting()) Level_load(level.current);
        else {
            level.current = level.previous;
            level.next = level.current;
        }

        Level_init(level.current);
    }

    Level_update(level.current, dt);
}

void LevelManager_draw()
{
    Level_draw(level.current);
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
    if (Level_isValid(nextLevel) || Level_isSpecial(nextLevel)) {
        level.next = nextLevel;
    }
}

static int LevelIsChanging() {
    return level.current != level.next;
}
