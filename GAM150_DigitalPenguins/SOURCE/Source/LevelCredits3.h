/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelCredits3.h
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */
#include "AEEngine.h"

#pragma once

AEGfxVertexList*	INSTRUCTOR_Mesh;
AEGfxTexture*  INSTRUCTOR_Texture;

AEGfxVertexList*	Chambers_Mesh;
AEGfxTexture*  Chambers_Texture;

/**
 * @brief Load LevelCredits3.
 */
void LevelCredits3_onLoad();

/**
 * @brief Initialize LevelCredits3.
 */
void LevelCredits3_onInit();

/**
 * @brief Update LevelCredits3.
 * @param dt Delta Time for updates.
 */
void LevelCredits3_onUpdate(float dt);

/**
 * @brief Shutdown LevelCredits3.
 */
void LevelCredits3_onShutdown();

/**
 * @brief Unload LevelCredits3.
 */
void LevelCredits3_onUnload();