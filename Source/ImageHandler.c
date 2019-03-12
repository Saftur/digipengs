/**
 * @file ImageHandler.c
 * @author Connor Meyers
 * @date 2019/01/10
 * @brief Imports images from a filename. The file should be located in the 'Assets' folder.
 */

#include "stdafx.h"		// Should be included first in every .c file!

#include "ImageHandler.h"
#include "Boulder.h"
#include "Camera.h"

LOADEDTEXTURES TEXTURES;

void ImageHandler_initializeTextures()
{
	TEXTURES.titleScreen_title = AEGfxTextureLoad("./Assets/TempTitle.png");
	AE_ASSERT_MESG(TEXTURES.titleScreen_title, "Failed to load/create TEXTURE: titleScreen_title");

	TEXTURES.titleScreen_startButton = AEGfxTextureLoad("./Assets/TempStartButton.png");
	AE_ASSERT_MESG(TEXTURES.titleScreen_startButton, "Failed to load/create TEXTURE: titleScreen_title");
	
	TEXTURES.titleScreen_button = AEGfxTextureLoad("./Assets/TempButton.png");
	AE_ASSERT_MESG(TEXTURES.titleScreen_button, "Failed to load/create TEXTURE: titleScreen_button");

	TEXTURES.titleScreen_exitButton = AEGfxTextureLoad("./Assets/TempExitButton.png");
	AE_ASSERT_MESG(TEXTURES.titleScreen_exitButton, "Failed to load/create TEXTURE: titleScreen_exitButton");

	TEXTURES.endScreen_youDied = AEGfxTextureLoad("./Assets/TempYouDied.png");
	AE_ASSERT_MESG(TEXTURES.endScreen_youDied, "Failed to load/create TEXTURE: endScreen_youDied");

	TEXTURES.endScreen_tryAgainButton = AEGfxTextureLoad("./Assets/TempTryAgainButton.png");
	AE_ASSERT_MESG(TEXTURES.endScreen_tryAgainButton, "Failed to load/create TEXTURE: endScreen_tryAgainButton");

	TEXTURES.endScreen_titleScreenButton = AEGfxTextureLoad("./Assets/TempTitleScreenButton.png");
	AE_ASSERT_MESG(TEXTURES.endScreen_titleScreenButton, "Failed to load/create TEXTURE: endScreen_titleScreenButton");

	TEXTURES.buttonSelected = AEGfxTextureLoad("./Assets/TempButtonSelected.png");
	AE_ASSERT_MESG(TEXTURES.buttonSelected, "Failed to load/create TEXTURE: buttonSelected");

    TEXTURES.test = AEGfxTextureLoad("./Assets/PlanetTexture.png");
    AE_ASSERT_MESG(TEXTURES.test, "Failed to load/create TEXTURE: test");

	TEXTURES.map = AEGfxTextureLoad("./Assets/Map.png");
	AE_ASSERT_MESG(TEXTURES.map, "Failed to load/create TEXTURE: map");

    TEXTURES.player = AEGfxTextureLoad("./Assets/Player.png");
    AE_ASSERT_MESG(TEXTURES.player, "Failed to load/create TEXTURE: Player");

    TEXTURES.playerRed = AEGfxTextureLoad("./Assets/PlayerRed.png");
    AE_ASSERT_MESG(TEXTURES.playerRed, "Failed to load/create TEXTURE: PlayerRed");


    TEXTURES.playerGreen = AEGfxTextureLoad("./Assets/PlayerGreen.png");
    AE_ASSERT_MESG(TEXTURES.playerGreen, "Failed to load/create TEXTURE: PlayerGreen");


    TEXTURES.boulder = AEGfxTextureLoad("./Assets/Boulder.png");
    AE_ASSERT_MESG(TEXTURES.boulder, "Failed to load/create TEXTURE: Boulder");

    TEXTURES.map_rightCornerTile = AEGfxTextureLoad("./Assets/RightTurnTile.png");
    AE_ASSERT_MESG(TEXTURES.map_rightCornerTile, "Failed to load/create TEXTURE: RightTurnTile");

    TEXTURES.map_leftCornerTile = AEGfxTextureLoad("./Assets/leftTurnTile.png");
    AE_ASSERT_MESG(TEXTURES.map_leftCornerTile, "Failed to load/create TEXTURE: leftTurnTile");

    TEXTURES.map_straightTile = AEGfxTextureLoad("./Assets/StraightTile.png");
    AE_ASSERT_MESG(TEXTURES.map_straightTile, "Failed to load/create TEXTURE: StraightTile");

    TEXTURES.titleScreen_levelEditorButton = AEGfxTextureLoad("./Assets/dad.png");
    AE_ASSERT_MESG(TEXTURES.titleScreen_levelEditorButton, "Failed to load/create TEXTURE: dad");

    TEXTURES.screen_separator = AEGfxTextureLoad("./Assets/ScreenSeparator.png");
    AE_ASSERT_MESG(TEXTURES.screen_separator, "Failed to load/create TEXTURE: ScreenSeparator");

	TEXTURES.font = AEGfxTextureLoad("./Assets/Comic_Sans.png");
	AE_ASSERT_MESG(TEXTURES.font, "Failed to load/create TEXTURE: font");


    TEXTURES.background = AEGfxTextureLoad("./Assets/background.png");
    AE_ASSERT_MESG(TEXTURES.background, "Failed to load/create TEXTURE: background");
}

void ImageHandler_shutdown() {
    AEGfxTextureUnload(TEXTURES.test);
    AEGfxTextureUnload(TEXTURES.titleScreen_title);
    AEGfxTextureUnload(TEXTURES.titleScreen_startButton);
    AEGfxTextureUnload(TEXTURES.titleScreen_button);
    AEGfxTextureUnload(TEXTURES.titleScreen_exitButton);
    AEGfxTextureUnload(TEXTURES.titleScreen_levelEditorButton);

    AEGfxTextureUnload(TEXTURES.map);
    AEGfxTextureUnload(TEXTURES.player);
    AEGfxTextureUnload(TEXTURES.playerGreen);
    AEGfxTextureUnload(TEXTURES.playerRed);
    AEGfxTextureUnload(TEXTURES.boulder);

    AEGfxTextureUnload(TEXTURES.endScreen_youDied);
    AEGfxTextureUnload(TEXTURES.endScreen_tryAgainButton);
    AEGfxTextureUnload(TEXTURES.endScreen_titleScreenButton);

    AEGfxTextureUnload(TEXTURES.buttonSelected);

    AEGfxTextureUnload(TEXTURES.map_leftCornerTile);
    AEGfxTextureUnload(TEXTURES.map_rightCornerTile);
    AEGfxTextureUnload(TEXTURES.map_straightTile);

    AEGfxTextureUnload(TEXTURES.screen_separator);
	AEGfxTextureUnload(TEXTURES.font);

    AEGfxTextureUnload(TEXTURES.background);
}

void ImageHandler_screenDrawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scaleX, float scaleY, float rotation, float alpha)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    // Set poisition 
    AEGfxSetFullTransform(position.x, position.y, AERadToDeg(rotation), scaleX, scaleY);
    // Set texture for object 2
    AEGfxTextureSet(texture, 0.0f, 0.0f);
    AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
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
    AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetTransparency(alpha);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}
