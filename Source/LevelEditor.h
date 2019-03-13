/**
 * @file LevelEditor.h
 * @author Brand Knutson
 * @date 2/20/2019
 * @brief Manage and create levels with a GUI.
 */

#pragma once

/**
 * @brief Update the level editor.
 * @param dt DeltaTime.
 */
void LevelEditor_init();

/**
 * @brief Update the level editor.
 * @param dt DeltaTime.
 */
void LevelEditor_update(float dt);

/**
 * @brief Shutdown the level editor.
 */
void LevelEditor_shutdown();