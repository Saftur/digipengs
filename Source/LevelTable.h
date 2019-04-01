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
	Level2,
    SplashScreen,
	TitleScreen,
	HighscoreScreen,
	EndScreen,
	LevelEditor,

	//Extra info
	LevelNum,
	LastLevel = LevelNum - 1,

    //Initial level.
    InitialLevel = SplashScreen,
} Levels;

/**
 * @brief Check if level is valid.
 * @param level The level to check if actually exists.
 * @return Whether or not the level is valid.
 */
int Level_isValid(Levels level);

/**
 * @brief Check if the level is
 * @param level The level to check if is special (I.E. quitting or restarting).
 * @return Whether or not the level is special.
 */
int Level_isSpecial(Levels level);

/**
 * @brief Load a level.
 * @param level Level to load.
 */
void Level_load(Levels level);

/**
 * @brief Initialize a level.
 * @param level Level to initialize.
 */
void Level_init(Levels level);

/**
 * @brief Update a level.
 * @param level Level to update.
 * @param dt DeltaTime for updates.
*/
void Level_update(Levels level, float dt);

/**
 * @brief Draw a level.
 * @param level Level to draw.
 */
void Level_draw(Levels level);

/**
 * @brief Shutdown a level.
 * @param level to shutdown.
*/
void Level_shutdown(Levels level);

/**
 * @brief Unload a level.
 * @param level to unload.
*/
void Level_unload(Levels level);
