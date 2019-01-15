/**
 * @file LevelTable.h
 * @author Brand Knutson
 * @date 1/10/2019
 * @brief List of all levels.
 */

#pragma once

/** 
 * @enum Levels
 * @brief Enum for easily accessing each level from the table.
 */
typedef enum
{
    LevelQuit = -3,
    LevelRestart = -2,
    LevelInvalid = -1,

    //Game levels.
    Level1,

    //Extra info
    LevelNum,
    LastLevel = LevelNum - 1,

    //Initial level.
    InitialLevel = Level1
} Levels;

/**
 * @brief Check if level is valid.
 * @param level The level to check if actually exists.
 * @return Whether or not the level is valid.
 */
int LevelIsValid(Levels level);

/**
 * @brief Check if the level is
 * @param level The level to check if is special (I.E. quitting or restarting).
 * @return Whether or not the level is special.
 */
int LevelIsSpecial(Levels level);

/**
 * @brief Load a level.
 * @param level Level to load.
 */
void ExecuteLevelLoad(Levels level);

/**
 * @brief Initialize a level.
 * @param level Level to initialize.
 */
void ExecuteLevelInit(Levels level);

/**
 * @brief Update a level.
 * @param level Level to update.
 * @param dt DeltaTime for updates.
*/
void ExecuteLevelUpdate(Levels level, float dt);

/**
 * @brief Shutdown a level.
 * @param level to shutdown.
*/
void ExecuteLevelShutdown(Levels level);

/**
 * @brief Unload a level.
 * @param level to unload.
*/
void ExecuteLevelUnload(Levels level);