/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LevelCredits4.c
 * @author Richard Folorunso
 * @date 1/10/2019
 * @brief First Level
 */

#include "stdafx.h"
#include "LevelCredits4.h"
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

void LevelCredits4_onLoad()
{
}

void LevelCredits4_onInit()
{
  Audio_playSfxGo();

  AEInputShowCursor(1);
  AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);

  //Object* DIGIPEN = Text_new("DIGIPEN", TEXTURES.font, (AEVec2) { -250, 250 }, 23, 42, (Color) { 1, 1, 1, 1 }, 0);

  AEGfxMeshStart();

  AEGfxTriAdd(
    -503.0f, -243.0f, 0x00FF00FF, 0.0f, 1.0f,
    503.0f, -243.0f, 0x00FFFF00, 1.0f, 1.0f,
    -503.0f, 243.0f, 0x00F00FFF, 0.0f, 0.0f);

  AEGfxTriAdd(
    503.0f, -243.0f, 0x00FFFFFF, 1.0f, 1.0f,
    503.0f, 243.0f, 0x00FFFFFF, 1.0f, 0.0f,
    -503.0f, 243.0f, 0x00FFFFFF, 0.0f, 0.0f);

  IMPORTANT_Mesh = AEGfxMeshEnd();
  AE_ASSERT_MESG(IMPORTANT_Mesh, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");

  IMPORTANT_Texture = AEGfxTextureLoad("./Assets/Credits/15.png");
  AE_ASSERT_MESG(IMPORTANT_Texture, "WHY IS THIS NOT WORKING, SOMEONE HELP PLEASE I'M DYING OVER HERE. ;)");
}

void LevelCredits4_onUpdate(float dt)
{
    NextRoomTimer += (2.0f * dt);
  
    AESysFrameStart();
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxSetPosition(0, 0);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    AEGfxSetPosition(0.0f, 0.0f);
    AEGfxTextureSet(IMPORTANT_Texture, 0.0f, 0.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(IMPORTANT_Mesh, AE_GFX_MDM_TRIANGLES);


    if (NextRoomTimer > 5.0f)
    {
      LevelManager_setNextLevel(TitleScreen);
    }
}

void LevelCredits4_onShutdown()
{
  NextRoomTimer = 0.0f;

  AEGfxMeshFree(IMPORTANT_Mesh);
  AEGfxTextureUnload(IMPORTANT_Texture);
}

void LevelCredits4_onUnload()
{
}
