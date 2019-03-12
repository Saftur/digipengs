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
    AEGfxTexture *test;                    ///< For testing purposes
	AEGfxTexture *titleScreen_title;       ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_startButton; ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_button;      ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_exitButton;  ///< the title for the titlescreen 
    AEGfxTexture *titleScreen_levelEditorButton; ///< Button for loading the level editor.
	AEGfxTexture *map;                     ///< A test map
    AEGfxTexture *player;                  ///< THE PLAYER
    AEGfxTexture *playerRed; ///< red player
    AEGfxTexture *playerGreen; ///< green player
    AEGfxTexture *boulder;                 ///< Boulder
	AEGfxTexture *endScreen_youDied; ///< button for the endscreen
	AEGfxTexture *endScreen_tryAgainButton; ///< button for the endscreen
	AEGfxTexture *endScreen_titleScreenButton; ///< button for the titlescreen
	AEGfxTexture *buttonSelected;
    AEGfxTexture *map_straightTile; ///< Straight tile segment for the map.
    AEGfxTexture *map_rightCornerTile; ///< Right corner tile segment for the map.
    AEGfxTexture *map_leftCornerTile; ///< Left corner tile segment for the map.
    AEGfxTexture *screen_separator; ///< Screen Seperator
    AEGfxTexture *background; ///< background art for the game

	AEGfxTexture *font;
	
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

void ImageHandler_shutdown();

/**
 * @brief Draws a texture onto a given mesh (Assumes mesh is a composite of triangles)
 * @param mesh The mesh to draw onto
 * @param texture The texture to draw onto the mesh
 * @param position Where to draw
 * @param scale Scale to draw the image at
 * @param rotation Rotation of the image
 * @param alpha Alpha of the image
 */
void ImageHandler_screenDrawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha);

void ImageHandler_screenDrawTextureWithOffset(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha, f32 offsetX, f32 offsetY);

/**
 * @brief Draws a texture onto a given mesh (Assumes mesh is a composite of triangles)
 * @param mesh The mesh to draw onto
 * @param texture The texture to draw onto the mesh
 * @param position Where to draw
 * @param scaleX Scale to draw the image at
 * @param scaleY Scale to draw the image at
 * @param rotation Rotation of the image
 * @param alpha Alpha of the imageas
 */
void ImageHandler_fullDrawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha);

void ImageHandler_fullDrawTextureWithOffset(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha, f32 offsetX, f32 offsetY);
