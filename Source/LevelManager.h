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
void LevelManager_init();

/**
 * @brief Update the level manager.
 */
void LevelManager_update(float dt);

/**
 * @brief Shutdown the level manager.
 */
void LevelManager_shutdown();

/**
 * @brief Determine if the current level is being restarted.
 */
int LevelManager_isRestarting();

/**
 * @brief Determine if the game is still running.
 */
int LevelManager_isRunning();

/**
 * @brief Set the next level to run.
 */
void LevelManager_setNextLevel(Levels nextLevel);