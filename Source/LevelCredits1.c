/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelCredits1.c
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */

#include "stdafx.h"
#include "LevelCredits1.h"
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
#include <AEExport.h>

static float NextRoomTimer = 0.0f;

void LevelCredits1_onLoad()
{
}

void LevelCredits1_onInit()
{
  AEInputShowCursor(1);
  AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);

  //Object* DIGIPEN = Text_new("DIGIPEN", TEXTURES.font, (AEVec2) { -250, 250 }, 23, 42, (Color) { 1, 1, 1, 1 }, 0);

  AEGfxMeshStart();

  AEGfxTriAdd(
    -534.0f, -40.0f, 0x00FF00FF, 0.0f, 1.0f,
    534.0f, -40.0f, 0x00FFFF00, 1.0f, 1.0f,
    -534.0f, 40.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    534.0f, -40.0f, 0x00FFFFFF, 1.0f, 1.0f,
    534.0f, 40.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -534.0f, 40.0f, 0x00FFFFFF, 0.0f, 0.0f);

  DIGIPEN_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(DIGIPEN_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  DIGIPEN_Texture = AEGfxTextureLoad("./Assets/Credits/0.png");
  AE_ASSERT_MESG(DIGIPEN_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  
  
  AEGfxMeshStart();

  AEGfxTriAdd(
    -92.0f, -26.0f, 0x00FF00FF, 0.0f, 1.0f,
    92.0f, -26.0f, 0x00FFFF00, 1.0f, 1.0f,
    -92.0f, 26.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    92.0f, -26.0f, 0x00FFFFFF, 1.0f, 1.0f,
    92.0f, 26.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -92.0f, 26.0f, 0x00FFFFFF, 0.0f, 0.0f);

  PRESENTS_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(PRESENTS_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  PRESENTS_Texture = AEGfxTextureLoad("./Assets/Credits/1.png");
  AE_ASSERT_MESG(PRESENTS_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");





  AEGfxMeshStart();

  AEGfxTriAdd(
    -413.0f, -39.0f, 0x00FF00FF, 0.0f, 1.0f,
    413.0f, -39.0f, 0x00FFFF00, 1.0f, 1.0f,
    -413.0f, 39.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    413.0f, -39.0f, 0x00FFFFFF, 1.0f, 1.0f,
    413.0f, 39.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -413.0f, 39.0f, 0x00FFFFFF, 0.0f, 0.0f);

  PRODUCTION_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(PRODUCTION_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  PRODUCTION_Texture = AEGfxTextureLoad("./Assets/Credits/2.png");
  AE_ASSERT_MESG(PRODUCTION_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");






  AEGfxMeshStart();

  AEGfxTriAdd(
    -299.0f, -41.0f, 0x00FF00FF, 0.0f, 1.0f,
    299.0f, -41.0f, 0x00FFFF00, 1.0f, 1.0f,
    -299.0f, 41.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    299.0f, -41.0f, 0x00FFFFFF, 1.0f, 1.0f,
    299.0f, 41.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -299.0f, 41.0f, 0x00FFFFFF, 0.0f, 0.0f);

  DIGITAL_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(DIGITAL_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  DIGITAL_Texture = AEGfxTextureLoad("./Assets/Credits/3.png");
  AE_ASSERT_MESG(DIGITAL_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");






  AEGfxMeshStart();

  AEGfxTriAdd(
    -187.0f, -32.0f, 0x00FF00FF, 0.0f, 1.0f,
    187.0f, -32.0f, 0x00FFFF00, 1.0f, 1.0f,
    -187.0f, 32.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    187.0f, -32.0f, 0x00FFFFFF, 1.0f, 1.0f,
    187.0f, 32.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -187.0f, 32.0f, 0x00FFFFFF, 0.0f, 0.0f);

  WWW_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(WWW_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  WWW_Texture = AEGfxTextureLoad("./Assets/Credits/4.png");
  AE_ASSERT_MESG(WWW_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");






  AEGfxMeshStart();

  AEGfxTriAdd(
    -574.0f, -28.0f, 0x00FF00FF, 0.0f, 1.0f,
    574.0f, -28.0f, 0x00FFFF00, 1.0f, 1.0f,
    -574.0f, 28.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    574.0f, -28.0f, 0x00FFFFFF, 1.0f, 1.0f,
    574.0f, 28.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -574.0f, 28.0f, 0x00FFFFFF, 0.0f, 0.0f);

  COPYRIGHT_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(COPYRIGHT_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  COPYRIGHT_Texture = AEGfxTextureLoad("./Assets/Credits/5.png");
  AE_ASSERT_MESG(COPYRIGHT_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");
}

void LevelCredits1_onUpdate(float dt)
{
    NextRoomTimer += (2.0f * dt);
  
    AESysFrameStart();
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxSetPosition(0, 0);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    AEGfxSetPosition(0.0f, 292.0f);
    AEGfxTextureSet(DIGIPEN_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(DIGIPEN_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, 205.0f);
    AEGfxTextureSet(PRESENTS_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(PRESENTS_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, 100.0f);
    AEGfxTextureSet(PRODUCTION_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(PRODUCTION_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, 0.0f);
    AEGfxTextureSet(DIGITAL_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(DIGITAL_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, -150.0f);
    AEGfxTextureSet(WWW_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(WWW_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, -250.0f);
    AEGfxTextureSet(COPYRIGHT_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(COPYRIGHT_Mesh, AE_GFX_MDM_TRIANGLES);


    if (NextRoomTimer > 5.0f)
    {
      LevelManager_setNextLevel(LevelCredits2);
    }
}

void LevelCredits1_onShutdown()
{
  NextRoomTimer = 0.0f;

  AEGfxMeshFree(DIGIPEN_Mesh);
  AEGfxTextureUnload(DIGIPEN_Texture);

  AEGfxMeshFree(PRESENTS_Mesh);
  AEGfxTextureUnload(PRESENTS_Texture);

  AEGfxMeshFree(PRODUCTION_Mesh);
  AEGfxTextureUnload(PRODUCTION_Texture);

  AEGfxMeshFree(DIGITAL_Mesh);
  AEGfxTextureUnload(DIGITAL_Texture);

  AEGfxMeshFree(WWW_Mesh);
  AEGfxTextureUnload(WWW_Texture);

  AEGfxMeshFree(COPYRIGHT_Mesh);
  AEGfxTextureUnload(COPYRIGHT_Texture);
}

void LevelCredits1_onUnload()
{
}
