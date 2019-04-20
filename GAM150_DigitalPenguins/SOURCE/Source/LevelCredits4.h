/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelCredits4.h
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */
#include "AEEngine.h"

#pragma once

AEGfxVertexList*	IMPORTANT_Mesh;
AEGfxTexture*  IMPORTANT_Texture;

/**
 * @brief Load LevelCredits4.
 */
void LevelCredits4_onLoad();

/**
 * @brief Initialize LevelCredits4.
 */
void LevelCredits4_onInit();

/**
 * @brief Update LevelCredits4.
 * @param dt Delta Time for updates.
 */
void LevelCredits4_onUpdate(float dt);

/**
 * @brief Shutdown LevelCredits4.
 */
void LevelCredits4_onShutdown();

/**
 * @brief Unload LevelCredits4.
 */
void LevelCredits4_onUnload();