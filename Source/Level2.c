/**
 * @file Level2.c
 * @author Richard Folorunso
 * @date 1/30/2019
 * @brief Test Level
 */

#include "stdafx.h"
#include "Level2.h"
#include "ObjectManager.h"
#include "Boulder.h"

void Level2_onLoad()
{
}

void Level2_onInit()
{
	ObjectManager_addObj(Boulder_new(BOULDER_TYPES.giant, (AEVec2) { 0, 0 }));
}

void Level2_onUpdate(float dt)
{
    UNREFERENCED_PARAMETER(dt);
}

void Level2_onShutdown()
{
}

void Level2_onUnload()
{
}
