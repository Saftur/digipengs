/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file SplashScreen.c
 * @author Arthur Bouvier
 * @date 1/23/2019
 * @brief Splash Screen implementation
 */

#include "stdafx.h"
#include "SplashScreen.h"
#include "ImageHandler.h"
#include "TextHandler.h"
#include "MeshHandler.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "Level2.h"
#include "Button.h"

static float timer;

static void splashDraw(Object *obj, void *data) {
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
	ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.splashScreen, (AEVec2) { 0, 0 }, 1024, 247, 0, 1);
}

void SplashScreen_onLoad()
{
}

void SplashScreen_onInit()
{
	ObjectManager_addObj(Object_new(NULL, NULL, splashDraw, NULL, NULL, "Title"));
    timer = 2.f;
}

void SplashScreen_onUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt); // don't think we need this for the title screen but it's here just in case
    timer -= dt;
    if (timer <= 0.f)
        LevelManager_setNextLevel(TitleScreen);
}

void SplashScreen_onShutdown()
{
}

void SplashScreen_onUnload()
{
}
