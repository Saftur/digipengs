/**
 * @file ImageHandler.h
 * @author Connor Meyers
 * @date 2019/01/10
 * @brief Imports images from a filename. The file should be located in the 'Assets' folder.
 */

#pragma once

#include "AEEngine.h"

/**
 * @struct LOADEDTEXTURES
 * @brief All of the different sprite textures in the game.
 */
struct LOADEDTEXTURES
{
    AEGfxTexture *test; ///< For testing purposes
}typedef LOADEDTEXTURES;

/**
 * @var extern LOADEDTEXTURES TEXTURES
 * @brief Global struct to access all of the loaded textures
 */
extern LOADEDTEXTURES TEXTURES; 

/**
 * @brief Loads all textures in the game
 */
void ImageHandler_initializeTextures();

/**
 * @brief Draws a texture onto a given mesh (Assumes mesh is a composite of triangles)
 * @param mesh The mesh to draw onto
 * @param texture The texture to draw onto the mesh
 * @param position Where to draw
 * @par Example: 
 * @code
 * ImageHandler_drawTexture(squareMesh, TEXTURES.test, (AEVec2) { 0, 0 });
 * @endcode
 */
void ImageHandler_drawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position);

/**
 * @brief Draws a texture onto a given mesh with a set alpha transparency (Assumes mesh is a composite of triangles)
 * @param mesh The mesh to draw onto
 * @param texture The texture to draw onto the mesh
 * @param position Where to draw
 * @param alpha The alpha value of the texture from 0 to 1
 * @par Example: 
 * @code
 * ImageHandler_drawTextureAlpha(squareMesh, TEXTURES.test, (AEVec2) { 0, 0 }, 0.5f);
 * @endcode
 */
void ImageHandler_drawTextureAlpha(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float alpha);