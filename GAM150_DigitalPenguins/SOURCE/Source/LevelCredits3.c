/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelCredits3.c
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */

#include "stdafx.h"
#include "LevelCredits3.h"
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

void LevelCredits3_onLoad()
{
}

void LevelCredits3_onInit()
{
  Audio_playSfxSet();

  AEInputShowCursor(1);
  AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);

  //Object* DIGIPEN = Text_new("DIGIPEN", TEXTURES.font, (AEVec2) { -250, 250 }, 23, 42, (Color) { 1, 1, 1, 1 }, 0);

  AEGfxMeshStart();

  AEGfxTriAdd(
    -102.0f, -28.0f, 0x00FF00FF, 0.0f, 1.0f,
    102.0f, -28.0f, 0x00FFFF00, 1.0f, 1.0f,
    -102.0f, 28.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    102.0f, -28.0f, 0x00FFFFFF, 1.0f, 1.0f,
    102.0f, 28.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -102.0f, 28.0f, 0x00FFFFFF, 0.0f, 0.0f);

  INSTRUCTOR_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(INSTRUCTOR_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  INSTRUCTOR_Texture = AEGfxTextureLoad("./Assets/Credits/12.png");
  AE_ASSERT_MESG(INSTRUCTOR_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  
  
  AEGfxMeshStart();

  AEGfxTriAdd(
    -434.0f, -67.0f, 0x00FF00FF, 0.0f, 1.0f,
    434.0f, -67.0f, 0x00FFFF00, 1.0f, 1.0f,
    -434.0f, 67.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    434.0f, -67.0f, 0x00FFFFFF, 1.0f, 1.0f,
    434.0f, 67.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -434.0f, 67.0f, 0x00FFFFFF, 0.0f, 0.0f);

  Chambers_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(Chambers_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  Chambers_Texture = AEGfxTextureLoad("./Assets/Credits/14.png");
  AE_ASSERT_MESG(Chambers_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");
}

void LevelCredits3_onUpdate(float dt)
{
    NextRoomTimer += (2.0f * dt);
  
    AESysFrameStart();
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxSetPosition(0, 0);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    AEGfxSetPosition(0.0f, 105.0f);
    AEGfxTextureSet(INSTRUCTOR_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(INSTRUCTOR_Mesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, 5.0f);
    AEGfxTextureSet(Chambers_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(Chambers_Mesh, AE_GFX_MDM_TRIANGLES);


    if (NextRoomTimer > 5.0f)
    {
      LevelManager_setNextLevel(LevelCredits4);
    }
}

void LevelCredits3_onShutdown()
{
  NextRoomTimer = 0.0f;

  AEGfxMeshFree(INSTRUCTOR_Mesh);
  AEGfxTextureUnload(INSTRUCTOR_Texture);

  AEGfxMeshFree(Chambers_Mesh);
  AEGfxTextureUnload(Chambers_Texture);
}

void LevelCredits3_onUnload()
{
}
