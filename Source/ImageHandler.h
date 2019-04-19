/**
 * @file ImageHandler.h
 * @author Connor Meyers
 * @date 2019/01/10
 * @brief Handles image loading & drawing.
 */

#pragma once

#include "AEEngine.h"

/**
 * @struct LOADEDTEXTURES
 * @brief All of the different sprite textures in the game.
 */
#pragma pack(push,1)
struct LOADEDTEXTURES
{
    AEGfxTexture *test;                    ///< For testing purposes

	AEGfxTexture *titleScreen_title;             ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_startButton;       ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_startButtonHover;       ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_startMultiButton;  ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_startMultiButtonHover;  ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_button;            ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_exitButton;        ///< the title for the titlescreen 
	AEGfxTexture *titleScreen_exitButtonHover;        ///< the title for the titlescreen 
    AEGfxTexture *titleScreen_levelEditorButton; ///< Button for loading the level editor.
    AEGfxTexture *titleScreen_levelEditorButtonHover; ///< Button for loading the level editor.
    AEGfxTexture *titleScreen_leaderboardButton; ///< Button for loading the leaderboard screen.
    AEGfxTexture *titleScreen_leaderboardButtonHover; ///< Button for loading the leaderboard. screen
	AEGfxTexture *titleScreen_creditsButton; ///< Button for loading the credits screen.
	AEGfxTexture *titleScreen_creditsButtonHover; ///< Button for loading the credits screen.

	AEGfxTexture *map;                     ///< A test map
    AEGfxTexture *player;                  ///< THE PLAYER
    AEGfxTexture *playerRed; ///< red player
    AEGfxTexture *playerGreen; ///< green player
    AEGfxTexture *particle;

    AEGfxTexture *boulder;                 ///< Boulder
    AEGfxTexture *polarbear; ///< background art for the game

	AEGfxTexture *endScreen_youDied; ///< button for the endscreen
	AEGfxTexture *endScreen_player1Wins; ///< Player 1 wins banner
	AEGfxTexture *endScreen_player2Wins; ///< Player 2 wins banner
	AEGfxTexture *endScreen_tryAgainButton; ///< button for the endscreen
	AEGfxTexture *endScreen_titleScreenButton; ///< button for the titlescreen

	AEGfxTexture *optionsScreen_dragButton;
	AEGfxTexture *optionsScreen_dragButtonHover;
	AEGfxTexture *optionsScreen_track;

	AEGfxTexture *buttonSelected;

    AEGfxTexture *map_straightTile; ///< Straight tile segment for the map.
    AEGfxTexture *map_rightCornerTile; ///< Right corner tile segment for the map.
    AEGfxTexture *map_leftCornerTile; ///< Left corner tile segment for the map.
    AEGfxTexture *map_startTile; ///< Start tile segment for the map.

    AEGfxTexture *screen_separator; ///< Screen Seperator
	AEGfxTexture *font;

    AEGfxTexture *splashScreen;
    AEGfxTexture *background; ///< background art for the game

	AEGfxTexture *le_helpMenu;
	AEGfxTexture *le_fullMenu; 

	AEGfxTexture *text_ready;
	AEGfxTexture *text_set;
	AEGfxTexture *text_go;
	AEGfxTexture *text_fl;
	AEGfxTexture *text_mapsaved;

	AEGfxTexture *text_lapleft1;
	AEGfxTexture *text_lapleft2;

	AEGfxTexture *controls_p1;
	AEGfxTexture *controls_p2;

	AEGfxTexture *powerup_pedastal;
	AEGfxTexture *powerup_blind;
	AEGfxTexture *powerup_speed;
	AEGfxTexture *powerup_phase;

	AEGfxTexture *blindObject;

	AEGfxTexture *text_playerGreen;
	AEGfxTexture *text_playerRed;
}typedef LOADEDTEXTURES;
#pragma pack(pop)

typedef struct Color {
    float r, g, b, a;
} Color;

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
 * @brief Set blend color
 * @param color Blend color
 */
void ImageHandler_setBlendColor(Color color);

/**
 * @brief Disable blend color
 */
void ImageHandler_disableBlendColor();

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
