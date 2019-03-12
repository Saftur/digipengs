/**
 * @file Background.c
 * @author Connor Meyers
 * @brief Object Header for the background
 */


#include "stdafx.h"

#include "Background.h"
#include "MeshHandler.h"

#define BACKGROUND_SIZE 64
#define BACKGROUND_TEXTURE TEXTURES.background
#define BACKGROUND_ANIMATION_SPEED 0.25f
#define BACKGROUND_FRAME_COUNT 17
#define BACKGROUND_SPRITE_ROWS 4
#define BACKGROUND_SPRITE_COLS 5

static int frameIndex_ = 0;
static AEVec2 offset_;
static float animationTimer_ = BACKGROUND_ANIMATION_SPEED;
static AEGfxVertexList *mesh_;

static AEVec2 getOffsets_(int);
static void draw_(float, float);
static AEGfxVertexList* getMesh_();

void Background_onDraw()
{
    float x, y;
    for (x = AEGfxGetWinMinX() - BACKGROUND_SIZE; x < AEGfxGetWinMaxX() + BACKGROUND_SIZE; x += BACKGROUND_SIZE)
    {
        for (y = AEGfxGetWinMinY() - BACKGROUND_SIZE; y < AEGfxGetWinMaxY() + BACKGROUND_SIZE; y += BACKGROUND_SIZE)
        {
            draw_(x, y);
        }
    }
}

void Background_shutdown(Object *obj)
{
    UNREFERENCED_PARAMETER(obj);
    AEGfxMeshFree(mesh_);
    mesh_ = NULL;
}

void Background_onUpdate(Object *obj, void *data, float dt)
{
    UNREFERENCED_PARAMETER(data);
    UNREFERENCED_PARAMETER(obj);

    if (animationTimer_ <= 0)
    {
        frameIndex_++;
        frameIndex_ %= BACKGROUND_FRAME_COUNT;
        offset_ = getOffsets_(frameIndex_);
        animationTimer_ = BACKGROUND_ANIMATION_SPEED;
    }
    else
    {
        animationTimer_ -= dt;
    }
}

/**
* @brief Create new background
* @return New background
*/
Object *Background_create()
{
    Object *ice = Object_new(NULL, Background_onUpdate, NULL, NULL, Background_shutdown, "Background");
    return ice;
}

static AEVec2 getOffsets_(int frameIndex)
{
    int row = frameIndex / BACKGROUND_SPRITE_COLS;
    int column = frameIndex % BACKGROUND_SPRITE_COLS;
    AEVec2 offset = { 0,0 };
    offset.x = ((f32)(column)) / ((f32)(BACKGROUND_SPRITE_COLS));
    offset.y = ((f32)(row)) / ((f32)(BACKGROUND_SPRITE_ROWS));

    return offset;
}

static void draw_(float x, float y)
{
    AEVec2 pos;
    pos.x = x;
    pos.y = y;
    ImageHandler_screenDrawTextureWithOffset(getMesh_(), BACKGROUND_TEXTURE, pos, BACKGROUND_SIZE, BACKGROUND_SIZE, 0, 1, offset_.x, offset_.y);
}
static AEGfxVertexList* getMesh_()
{
    if (mesh_)
        return mesh_;
    else
        return mesh_ = MeshHandler_createSquareMesh(0.5f, 0.5f, 1.0f / BACKGROUND_SPRITE_COLS, 1.0f / BACKGROUND_SPRITE_ROWS);
}
