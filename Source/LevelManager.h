/**
 * @file LevelManager.h
 * @author Brand Knutson
 * @date 1/10/2019
 * @brief Handle loading and switching levels.
 */

#pragma once
#include "LevelTable.h"

/**
 * @brief Initialize the level manager.
 */
void LevelManagerInit();

/**
 * @brief Update the level manager.
 */
void LevelManagerUpdate(float dt);

/**
 * @brief Shutdown the level manager.
 */
void LevelManagerShutdown();

/**
 * @brief Determine if the current level is being restarted.
 */
int LevelManagerIsRestarting();

/**
 * @brief Determine if the game is still running.
 */
int LevelManagerIsRunning();

/**
 * @brief Set the next level to run.
 */
void LevelManagerSetNextLevel(Levels nextLevel);