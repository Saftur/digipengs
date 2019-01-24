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
    TEXTURES.test = AEGfxTextureLoad("./Assets/PlanetTexture.png");
    AE_ASSERT_MESG(TEXTURES.test, "Failed to load/create TEXTURE: test");
}

void ImageHandler_drawTexture(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    // Set poisition 
    AEGfxSetPosition(position.x, position.y);
    // Set texture for object 2
    AEGfxTextureSet(texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    // Drawing the mesh (list of triangles)
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void ImageHandler_drawTextureAlpha(AEGfxVertexList *mesh, AEGfxTexture *texture, AEVec2 position, float alpha)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    // Set poisition 
    AEGfxSetPosition(position.x, position.y);
    // Set texture for object 2
    AEGfxTextureSet(texture, 0.0f, 0.0f);
    AEGfxSetTransparency(alpha);
    // Drawing the mesh (list of triangles)
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}