/**
 * @file ImageHandler.c
 * @author Connor Meyers
 * @date 2019/01/10
 * @brief Handles image loading & drawing.
 */

#include "stdafx.h"		// Should be included first in every .c file!

#include "ImageHandler.h"
#include "Boulder.h"
#include "Camera.h"

#define BUFFER_SIZE 100

LOADEDTEXTURES TEXTURES;

static Color blendColor;

static void loadTexture(AEGfxTexture **texture, const char *name) {
    char filename[BUFFER_SIZE];
    sprintf_s(filename, BUFFER_SIZE, "./Assets/%s.png", name);
    *texture = AEGfxTextureLoad(filename);
    AE_ASSERT_MESG(*texture, "Failed to load/create TEXTURE: %s", name);
}

void ImageHandler_initializeTextures()
{
    loadTexture(&TEXTURES.test, "PlanetTexture");

    loadTexture(&TEXTURES.titleScreen_title, "Logo");
    loadTexture(&TEXTURES.titleScreen_startButton, "SinglePlayer");
    loadTexture(&TEXTURES.titleScreen_startButtonHover, "SinglePlayerHover");
    loadTexture(&TEXTURES.titleScreen_startMultiButton, "Multi");
    loadTexture(&TEXTURES.titleScreen_startMultiButtonHover, "MultiHover");
    loadTexture(&TEXTURES.titleScreen_button, "TempButton");
    loadTexture(&TEXTURES.titleScreen_exitButton, "Exit");
    loadTexture(&TEXTURES.titleScreen_exitButtonHover, "ExitHover");
    loadTexture(&TEXTURES.titleScreen_levelEditorButton, "Level_Editor");
    loadTexture(&TEXTURES.titleScreen_levelEditorButtonHover, "Level EditorHover");
    loadTexture(&TEXTURES.titleScreen_leaderboardButton, "Leader");
    loadTexture(&TEXTURES.titleScreen_leaderboardButtonHover, "LeaderHover");

    loadTexture(&TEXTURES.map, "Map");
    loadTexture(&TEXTURES.player, "Player");
    loadTexture(&TEXTURES.playerRed, "PlayerRed");
    loadTexture(&TEXTURES.playerGreen, "PlayerGreen");
    loadTexture(&TEXTURES.particle, "Star2");

    loadTexture(&TEXTURES.boulder, "Boulder");
    loadTexture(&TEXTURES.polarbear, "PolarBear");

    loadTexture(&TEXTURES.endScreen_youDied, "TempYouDied");
    loadTexture(&TEXTURES.endScreen_player1Wins, "Player1Wins");
    loadTexture(&TEXTURES.endScreen_player2Wins, "Player2Wins");
    loadTexture(&TEXTURES.endScreen_tryAgainButton, "TempTryAgainButton");
    loadTexture(&TEXTURES.endScreen_titleScreenButton, "TempTitleScreenButton");

	loadTexture(&TEXTURES.optionsScreen_dragButton, "Drag_Button");
	loadTexture(&TEXTURES.optionsScreen_dragButtonHover, "Drag_Button_Hover");
	loadTexture(&TEXTURES.optionsScreen_track, "Track");

    loadTexture(&TEXTURES.buttonSelected, "TempButtonSelected");

    loadTexture(&TEXTURES.map_straightTile, "StraightTile");
    loadTexture(&TEXTURES.map_rightCornerTile, "RightTurnTile");
    loadTexture(&TEXTURES.map_leftCornerTile, "LeftTurnTile");
    loadTexture(&TEXTURES.map_startTile, "StartTile");

    loadTexture(&TEXTURES.screen_separator, "ScreenSeparator");
    loadTexture(&TEXTURES.font, "Comic_Sans");

    loadTexture(&TEXTURES.splashScreen, "DigiPen_RED_1024px");
    loadTexture(&TEXTURES.background, "waterstrip_strip161");

	loadTexture(&TEXTURES.le_helpMenu, "LEControls_Help");
	loadTexture(&TEXTURES.le_fullMenu, "LEControls");

	loadTexture(&TEXTURES.text_ready, "Text_Ready");
	loadTexture(&TEXTURES.text_set, "Text_Set");
	loadTexture(&TEXTURES.text_go, "Text_Go");

	loadTexture(&TEXTURES.text_fl, "Text_FinalLap");
	loadTexture(&TEXTURES.text_mapsaved, "Text_MapSaved");

	loadTexture(&TEXTURES.text_lapleft1, "Text_1LapLeft");
	loadTexture(&TEXTURES.text_lapleft2, "Text_2LapLeft");

	loadTexture(&TEXTURES.controls_p1, "controls_p1");
	loadTexture(&TEXTURES.controls_p2, "controls_p2");


	loadTexture(&TEXTURES.powerup_pedastal, "powerup_pedestal");
	loadTexture(&TEXTURES.powerup_blind, "powerup_blind");
	loadTexture(&TEXTURES.powerup_speed, "powerup_speed");
	loadTexture(&TEXTURES.powerup_phase, "powerup_phase");

	loadTexture(&TEXTURES.text_playerGreen, "text_playerGreen");
	loadTexture(&TEXTURES.text_playerRed, "text_playerRed");

	loadTexture(&TEXTURES.blindObject, "blindObject");
}

void ImageHandler_shutdown() {
    for (unsigned i = 0; i < sizeof(LOADEDTEXTURES) / sizeof(void*); i++)
        AEGfxTextureUnload(((AEGfxTexture**)(&TEXTURES))[i]);
}

void ImageHandler_setBlendColor(Color color) {
    blendColor = color;
}

void ImageHandler_disableBlendColor() {
    blendColor = (Color) { 0, 0, 0, 0 };
}

void ImageHandler_screenDrawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    // Set poisition 
    AEGfxSetFullTransform(position.x, position.y, AERadToDeg(rotation), scaleX, scaleY);
    // Set texture for object 2
    AEGfxTextureSet(texture, 0.0f, 0.0f);
    AEGfxSetBlendColor(blendColor.r, blendColor.g, blendColor.b, blendColor.a);
    AEGfxSetTransparency(alpha);
    // Drawing the mesh (list of triangles)
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void ImageHandler_screenDrawTextureWithOffset(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha, f32 offsetX, f32 offsetY)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	// Set poisition 
	AEGfxSetFullTransform(position.x, position.y, AERadToDeg(rotation), scaleX, scaleY);
	// Set texture for object 2
	AEGfxTextureSet(texture, offsetX, offsetY);
    AEGfxSetBlendColor(blendColor.r, blendColor.g, blendColor.b, blendColor.a);
	AEGfxSetTransparency(alpha);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void ImageHandler_fullDrawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    // Set poisition 
    AEVec2 newPos = Camera_apply(Camera_getCurr(), position);
    AEGfxSetFullTransform(newPos.x, newPos.y, AERadToDeg(rotation) + Camera_rot(), scaleX * Camera_scl(), scaleY * Camera_scl());
    // Set texture for object 2
    AEGfxTextureSet(texture, 0.0f, 0.0f);
    AEGfxSetBlendColor(blendColor.r, blendColor.g, blendColor.b, blendColor.a);
    AEGfxSetTransparency(alpha);
    // Drawing the mesh (list of triangles)
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void ImageHandler_fullDrawTextureWithOffset(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha, f32 offsetX, f32 offsetY)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	// Set poisition 
	AEVec2 newPos = Camera_apply(Camera_getCurr(), position);
	AEGfxSetFullTransform(newPos.x, newPos.y, AERadToDeg(rotation) + Camera_rot(), scaleX * Camera_scl(), scaleY * Camera_scl());
	// Set texture for object 2
	AEGfxTextureSet(texture, offsetX, offsetY);
    AEGfxSetBlendColor(blendColor.r, blendColor.g, blendColor.b, blendColor.a);
	AEGfxSetTransparency(alpha);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}
