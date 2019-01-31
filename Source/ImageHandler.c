/**
 * @file ImageHandler.c
 * @author Connor Meyers
 * @date 2019/01/10
 * @brief Imports images from a filename. The file should be located in the 'Assets' folder.
 */

#include "stdafx.h"		// Should be included first in every .c file!

#include "ImageHandler.h"
#include "Boulder.h"

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

    TEXTURES.test = AEGfxTextureLoad("./Assets/PlanetTexture.png");
    AE_ASSERT_MESG(TEXTURES.test, "Failed to load/create TEXTURE: test");

    TEXTURES.player = AEGfxTextureLoad("./Assets/Player.png");
    AE_ASSERT_MESG(TEXTURES.player, "Failed to load/create TEXTURE: Player");
}

void ImageHandler_shutdown() {
	AEGfxTextureUnload(TEXTURES.test);
	AEGfxTextureUnload(TEXTURES.titleScreen_title);
	AEGfxTextureUnload(TEXTURES.titleScreen_startButton);
	AEGfxTextureUnload(TEXTURES.titleScreen_button);
	AEGfxTextureUnload(TEXTURES.titleScreen_exitButton);
    AEGfxTextureUnload(TEXTURES.player);
}

void ImageHandler_drawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float rotation)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    // Set poisition 
    AEGfxSetFullTransform(position.x, position.y, AERadToDeg(rotation), 1.0f, 1.0f);
    // Set texture for object 2
    AEGfxTextureSet(texture, 0.0f, 0.0f);
    AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    // Drawing the mesh (list of triangles)
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void ImageHandler_fullDrawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, AEVec2 scale, float rotation, float alpha)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    // Set poisition 
    AEGfxSetFullTransform(position.x, position.y, AERadToDeg(rotation), scale.x, scale.y);
    // Set texture for object 2
    AEGfxTextureSet(texture, 0.0f, 0.0f);
    AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetTransparency(alpha);
    // Drawing the mesh (list of triangles)
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}