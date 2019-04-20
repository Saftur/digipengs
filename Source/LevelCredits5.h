/**
 * @file LevelCredits5.h
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */
#include "AEEngine.h"

#pragma once

AEGfxVertexList*	FMOD_Mesh;
AEGfxTexture*  FMOD_Texture;

/**
 * @brief Load LevelCredits5.
 */
void LevelCredits5_onLoad();

/**
 * @brief Initialize LevelCredits5.
 */
void LevelCredits5_onInit();

/**
 * @brief Update LevelCredits5.
 * @param dt Delta Time for updates.
 */
void LevelCredits5_onUpdate(float dt);

/**
 * @brief Shutdown LevelCredits5.
 */
void LevelCredits5_onShutdown();

/**
 * @brief Unload LevelCredits5.
 */
void LevelCredits5_onUnload();