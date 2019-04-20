/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelCredits1.h
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */
#include "AEEngine.h"

#pragma once

AEGfxVertexList*	DIGIPEN_Mesh;
AEGfxTexture*  DIGIPEN_Texture;

AEGfxVertexList*	PRESENTS_Mesh;
AEGfxTexture*  PRESENTS_Texture;

AEGfxVertexList*	PRODUCTION_Mesh;
AEGfxTexture*  PRODUCTION_Texture;

AEGfxVertexList*	DIGITAL_Mesh;
AEGfxTexture*  DIGITAL_Texture;

AEGfxVertexList*	WWW_Mesh;
AEGfxTexture*  WWW_Texture;

AEGfxVertexList*	COPYRIGHT_Mesh;
AEGfxTexture*  COPYRIGHT_Texture;

/**
 * @brief Load LevelCredits1.
 */
void LevelCredits1_onLoad();

/**
 * @brief Initialize LevelCredits1.
 */
void LevelCredits1_onInit();

/**
 * @brief Update LevelCredits1.
 * @param dt Delta Time for updates.
 */
void LevelCredits1_onUpdate(float dt);

/**
 * @brief Shutdown LevelCredits1.
 */
void LevelCredits1_onShutdown();

/**
 * @brief Unload LevelCredits1.
 */
void LevelCredits1_onUnload();