/**
 * @file LevelEditorLevel.c
 * @author Brand Knutson
 * @date Wednesday, February 20, 2019
 * @brief Level editor level.
 */

#include "stdafx.h"
#include "LevelEditorLevel.h"
#include "LevelEditor.h"
#include "Camera.h"

void LevelEditorLevel_onLoad()
{
}

void LevelEditorLevel_onInit()
{
    //Camera_new((AEVec2) { 1200, -1000 }, 0.16f, 0, (AEVec2) { 0, 0 }, (AEVec2) { 800, 600 });
    LevelEditor_init();
}

void LevelEditorLevel_onUpdate(float dt)
{
    LevelEditor_update(dt);

    Camera *cam = Camera_getCurr();
    if (AEInputCheckCurr('Q'))
        cam->worldScale *= 0.9f;
    if (AEInputCheckCurr('E'))
        cam->worldScale *= 1.1f;

    float camSpeed = 2.f;
    AEVec2 camMov = { 0,0 };
    if (AEInputCheckCurr('W')) camMov.y = ceilf(camSpeed * (1 / cam->worldScale));
    if (AEInputCheckCurr('A')) camMov.x = floorf(-camSpeed * (1 / cam->worldScale));
    if (AEInputCheckCurr('S')) camMov.y = floorf(-camSpeed * (1 / cam->worldScale));
    if (AEInputCheckCurr('D')) camMov.x = ceilf(camSpeed * (1 / cam->worldScale));

    if(cam) AEVec2Add(&cam->worldPos, &cam->worldPos, &camMov);
}

void LevelEditorLevel_onShutdown()
{
    LevelEditor_shutdown(); 
    Camera_clear();
    Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, (AEVec2) { 800, 600 });
}

void LevelEditorLevel_onUnload()
{
}
