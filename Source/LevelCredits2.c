/**
 * @file LevelCredits2.c
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */

#include "stdafx.h"
#include "LevelCredits2.h"
#include "AEEngine.h"
#include "ImageHandler.h"
#include "TextHandler.h"
#include "MeshHandler.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "Level2.h"
#include "Button.h"
#include "DragButton.h"
#include "Background.h"
#include "AudioHandler.h"
#include "AudioHandler.h"
#include <AEExport.h>

static float NextRoomTimer = 0.0f;

static float LeftJustified = -2048.0f;
static float RightJustified = 2048.0f;

void LevelCredits2_onLoad()
{
}

void LevelCredits2_onInit()
{
  Audio_playSfxReady();

  AEInputShowCursor(1);
  AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);

  //Object* DIGIPEN = Text_new("DIGIPEN", TEXTURES.font, (AEVec2) { -250, 250 }, 23, 42, (Color) { 1, 1, 1, 1 }, 0);

  AEGfxMeshStart();

  AEGfxTriAdd(
    -119.0f, -23.0f, 0x00FF00FF, 0.0f, 1.0f,
    119.0f, -23.0f, 0x00FFFF00, 1.0f, 1.0f,
    -119.0f, 23.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    119.0f, -23.0f, 0x00FFFFFF, 1.0f, 1.0f,
    119.0f, 23.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -119.0f, 23.0f, 0x00FFFFFF, 0.0f, 0.0f);

  DEVELOPED_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(DEVELOPED_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  DEVELOPED_Texture = AEGfxTextureLoad("./Assets/Credits/6.png");
  AE_ASSERT_MESG(DEVELOPED_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  
  AEGfxMeshStart();

  AEGfxTriAdd(
    -306.0f, -34.0f, 0x00FF00FF, 0.0f, 1.0f,
    306.0f, -34.0f, 0x00FFFF00, 1.0f, 1.0f,
    -306.0f, 34.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    306.0f, -34.0f, 0x00FFFFFF, 1.0f, 1.0f,
    306.0f, 34.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -306.0f, 34.0f, 0x00FFFFFF, 0.0f, 0.0f);

  BRAND_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(BRAND_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  BRAND_Texture = AEGfxTextureLoad("./Assets/Credits/7.png");
  AE_ASSERT_MESG(BRAND_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");






  AEGfxMeshStart();

  AEGfxTriAdd(
    -306.0f, -35.0f, 0x00FF00FF, 0.0f, 1.0f,
    306.0f, -35.0f, 0x00FFFF00, 1.0f, 1.0f,
    -306.0f, 35.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    306.0f, -35.0f, 0x00FFFFFF, 1.0f, 1.0f,
    306.0f, 35.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -306.0f, 35.0f, 0x00FFFFFF, 0.0f, 0.0f);

  ARTHUR_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(ARTHUR_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  ARTHUR_Texture = AEGfxTextureLoad("./Assets/Credits/8.png");
  AE_ASSERT_MESG(ARTHUR_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");





  AEGfxMeshStart();

  AEGfxTriAdd(
    -306.0f, -35.0f, 0x00FF00FF, 0.0f, 1.0f,
    306.0f, -35.0f, 0x00FFFF00, 1.0f, 1.0f,
    -306.0f, 35.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    306.0f, -35.0f, 0x00FFFFFF, 1.0f, 1.0f,
    306.0f, 35.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -306.0f, 35.0f, 0x00FFFFFF, 0.0f, 0.0f);

  CONNOR_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(CONNOR_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  CONNOR_Texture = AEGfxTextureLoad("./Assets/Credits/9.png");
  AE_ASSERT_MESG(CONNOR_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");





  AEGfxMeshStart();

  AEGfxTriAdd(
    -369.0f, -35.0f, 0x00FF00FF, 0.0f, 1.0f,
    369.0f, -35.0f, 0x00FFFF00, 1.0f, 1.0f,
    -369.0f, 35.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    369.0f, -35.0f, 0x00FFFFFF, 1.0f, 1.0f,
    369.0f, 35.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -369.0f, 35.0f, 0x00FFFFFF, 0.0f, 0.0f);

  RICHARD_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(RICHARD_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  RICHARD_Texture = AEGfxTextureLoad("./Assets/Credits/10.png");
  AE_ASSERT_MESG(RICHARD_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");





  AEGfxMeshStart();

  AEGfxTriAdd(
    -328.0f, -35.0f, 0x00FF00FF, 0.0f, 1.0f,
    328.0f, -35.0f, 0x00FFFF00, 1.0f, 1.0f,
    -328.0f, 35.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    328.0f, -35.0f, 0x00FFFFFF, 1.0f, 1.0f,
    328.0f, 35.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -328.0f, 35.0f, 0x00FFFFFF, 0.0f, 0.0f);

  PARKER_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(PARKER_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  PARKER_Texture = AEGfxTextureLoad("./Assets/Credits/11.png");
  AE_ASSERT_MESG(PARKER_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");
}

void LevelCredits2_onUpdate(float dt)
{
    NextRoomTimer += (2.0f * dt);

    LeftJustified += (2000.0f * dt);
    RightJustified -= (2000.0f * dt);

    LeftJustified = fminf(0, LeftJustified);
    RightJustified = fmaxf(0, RightJustified);

  
    AESysFrameStart();
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxSetPosition(0, 0);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    AEGfxSetPosition(0.0f, 292.0f);
    AEGfxTextureSet(DEVELOPED_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(DEVELOPED_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(LeftJustified, 205.0f);
    AEGfxTextureSet(BRAND_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(BRAND_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(RightJustified, 105.0f);
    AEGfxTextureSet(ARTHUR_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(ARTHUR_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(LeftJustified, 5.0f);
    AEGfxTextureSet(CONNOR_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(CONNOR_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(RightJustified, -95.0f);
    AEGfxTextureSet(RICHARD_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(RICHARD_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(LeftJustified, -195.0f);
    AEGfxTextureSet(PARKER_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(PARKER_Mesh, AE_GFX_MDM_TRIANGLES);

    


    if (NextRoomTimer > 5.0f)
    {
      LevelManager_setNextLevel(LevelCredits3);
    }
}

void LevelCredits2_onShutdown()
{
  NextRoomTimer = 0.0f;
  LeftJustified = -2048.0f;
  RightJustified = 2048.0f;

  AEGfxMeshFree(DEVELOPED_Mesh);
  AEGfxTextureUnload(DEVELOPED_Texture);

  AEGfxMeshFree(BRAND_Mesh);
  AEGfxTextureUnload(BRAND_Texture);

  AEGfxMeshFree(ARTHUR_Mesh);
  AEGfxTextureUnload(ARTHUR_Texture);

  AEGfxMeshFree(CONNOR_Mesh);
  AEGfxTextureUnload(CONNOR_Texture);

  AEGfxMeshFree(RICHARD_Mesh);
  AEGfxTextureUnload(RICHARD_Texture);

  AEGfxMeshFree(PARKER_Mesh);
  AEGfxTextureUnload(PARKER_Texture);
}

void LevelCredits2_onUnload()
{
}
