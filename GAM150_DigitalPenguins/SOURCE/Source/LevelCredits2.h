/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelCredits2.h
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */
#include "AEEngine.h"

#pragma once

AEGfxVertexList*	DEVELOPED_Mesh;
AEGfxTexture*  DEVELOPED_Texture;

AEGfxVertexList*	BRAND_Mesh;
AEGfxTexture*  BRAND_Texture;

AEGfxVertexList*	ARTHUR_Mesh;
AEGfxTexture*  ARTHUR_Texture;

AEGfxVertexList*	CONNOR_Mesh;
AEGfxTexture*  CONNOR_Texture;

AEGfxVertexList*	RICHARD_Mesh;
AEGfxTexture*  RICHARD_Texture;

AEGfxVertexList*	PARKER_Mesh;
AEGfxTexture*  PARKER_Texture;

/**
 * @brief Load LevelCredits2.
 */
void LevelCredits2_onLoad();

/**
 * @brief Initialize LevelCredits2.
 */
void LevelCredits2_onInit();

/**
 * @brief Update LevelCredits2.
 * @param dt Delta Time for updates.
 */
void LevelCredits2_onUpdate(float dt);

/**
 * @brief Shutdown LevelCredits2.
 */
void LevelCredits2_onShutdown();

/**
 * @brief Unload LevelCredits2.
 */
void LevelCredits2_onUnload();