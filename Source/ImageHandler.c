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

    TEXTURES.test = AEGfxTextureLoad("./Assets/PlanetTexture.png");
    AE_ASSERT_MESG(TEXTURES.test, "Failed to load/create TEXTURE: test");

	TEXTURES.map = AEGfxTextureLoad("./Assets/Map.png");
	AE_ASSERT_MESG(TEXTURES.map, "Failed to load/create TEXTURE: map");

    TEXTURES.player = AEGfxTextureLoad("./Assets/Player.png");
    AE_ASSERT_MESG(TEXTURES.player, "Failed to load/create TEXTURE: Player");

    TEXTURES.boulder = AEGfxTextureLoad("./Assets/Boulder.png");
    AE_ASSERT_MESG(TEXTURES.boulder, "Failed to load/create TEXTURE: Boulder");
}

void ImageHandler_shutdown() {
	AEGfxTextureUnload(TEXTURES.test);
	AEGfxTextureUnload(TEXTURES.titleScreen_title);
	AEGfxTextureUnload(TEXTURES.titleScreen_startButton);
	AEGfxTextureUnload(TEXTURES.titleScreen_button);
	AEGfxTextureUnload(TEXTURES.titleScreen_exitButton);
	AEGfxTextureUnload(TEXTURES.map);
    AEGfxTextureUnload(TEXTURES.player);
}

void ImageHandler_drawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float rotation)
{
    ImageHandler_fullDrawTexture(mesh, texture, position, 1.f, rotation, 1.f);
}

void ImageHandler_fullDrawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float scale, float rotation, float alpha)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    // Set poisition 
    float rotRad = AEDegToRad(Camera_rot());
    AEVec2 localPos;
    AEVec2Sub(&localPos, &position, &Camera_getCurr()->worldPos);
    AEVec2 newPos;
    newPos.x = cosf(rotRad) * localPos.x - sinf(rotRad) * localPos.y;
    newPos.y = sinf(rotRad) * localPos.x + cosf(rotRad) * localPos.y;
    newPos.x *= Camera_scl();
    newPos.y *= Camera_scl();
    AEGfxSetFullTransform(newPos.x, newPos.y, AERadToDeg(rotation) + Camera_rot(), scale * Camera_scl(), scale * Camera_scl());
    // Set texture for object 2
    AEGfxTextureSet(texture, 0.0f, 0.0f);
    AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetTransparency(alpha);
    // Drawing the mesh (list of triangles)
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}
