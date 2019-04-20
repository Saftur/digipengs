/**
 * @file Level1.h
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */
#include "AEEngine.h"

#pragma once

AEGfxVertexList*	pMesh2;				// Pointer to Mesh (Model)
AEGfxTexture *pTex1;					// Pointer to Texture (Image)

/**
 * @brief Load Level1.
 */
void Level1_onLoad();

/**
 * @brief Initialize Level1.
 */
void Level1_onInit();

/**
 * @brief Update Level1.
 * @param dt Delta Time for updates.
 */
void Level1_onUpdate(float dt);

/**
 * @brief Shutdown Level1.
 */
void Level1_onShutdown();

/**
 * @brief Unload Level1.
 */
void Level1_onUnload();