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
 * @param dt Delta Time for updates.
 */
void LevelManager_update(float dt);

/**
 * @brief Shutdown the level manager.
 */
void LevelManager_shutdown();

/**
 * @brief Determine if the current level is being restarted.
 * @return Whether or not the current level is restarting.
 */
int LevelManager_isRestarting();

/**
 * @brief Determine if the game is still running.
 * @return Whether or not the LevelManager is currently running.
 */
int LevelManager_isRunning();

/**
 * @brief Set the next level to run.
 * @param nextLevel The next level to load.
 */
void LevelManager_setNextLevel(Levels nextLevel);