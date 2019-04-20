/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Level1.c
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */

#include "stdafx.h"
#include "Level1.h"
#include "AEEngine.h"

void Level1_onLoad()
{
}

void Level1_onInit()
{
  AEGfxMeshStart();

  AEGfxTriAdd(
    -30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
    30.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
    -30.0f, 30.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    30.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
    30.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -30.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

  pMesh2 = AEGfxMeshEnd();
  AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");


  pTex1 = AEGfxTextureLoad("./Assets/PlanetTexture.png");
  AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");


  AEGfxSetBackgroundColor(0.4f, 0.4f, 0.4f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

void Level1_onUpdate(float dt)
{
    UNREFERENCED_PARAMETER(dt);
   AESysFrameStart();
    //AEInputUpdate();
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxSetPosition(0, 0);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetPosition(100.0f, -60.0f);
    AEGfxTextureSet(pTex1, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
    //AESysFrameEnd();
}

void Level1_onShutdown()
{
  AEGfxMeshFree(pMesh2);
  AEGfxTextureUnload(pTex1);
  //AESysExit();
}

void Level1_onUnload()
{
}
