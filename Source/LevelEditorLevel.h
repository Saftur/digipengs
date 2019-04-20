/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelEditorLevel.h
 * @author Brand Knutson
 * @date Wednesday, February 20, 2019
 * @brief Level editor level.
 */

#pragma once
/**
 * @brief Load Level.
 */
void LevelEditorLevel_onLoad();

/**
 * @brief Initialize Level.
 */
void LevelEditorLevel_onInit();

/**
 * @brief Update Level.
 */
void LevelEditorLevel_onUpdate(float dt);

/**
 * @brief Shutdown Level.
 */
void LevelEditorLevel_onShutdown();

/**
 * @brief Unload Level.
 */
void LevelEditorLevel_onUnload();