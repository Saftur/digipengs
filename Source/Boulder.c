/**
 * @file Boulder.c
 * @author Connor Meyers
 * @date 2019/01/23
 * @brief Object implementation for the Boulder obstacle
 */

#include "stdafx.h"

#include "Boulder.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Object.h"

typedef struct BoulderInfo
{
    AEGfxVertexList *mesh;
    AEGfxTexture    *texture;
}BoulderInfo;

struct _boulderTypes BOULDER_TYPES;

static void initalizeInfo(BoulderInfo * * info, AEGfxTexture *texture, float size)
{
    *info = (BoulderInfo *)malloc(sizeof(BoulderInfo));
    (*info)->texture = texture;
    (*info)->mesh = MeshHandler_createSquareMesh(size, size);
}

void Boulder_intialize()
{
    initalizeInfo(&BOULDER_TYPES.tiny,   BOULDER_TINY_TEXTURE,   BOULDER_TINY_SIZE);
    initalizeInfo(&BOULDER_TYPES.normal, BOULDER_NORMAL_TEXTURE, BOULDER_NORMAL_SIZE);
    initalizeInfo(&BOULDER_TYPES.big,    BOULDER_BIG_TEXTURE,    BOULDER_BIG_SIZE);
    initalizeInfo(&BOULDER_TYPES.giant,  BOULDER_GIANT_TEXTURE,  BOULDER_GIANT_SIZE);
}

void Boulder_shutdown()
{
    AEGfxMeshFree(BOULDER_TYPES.tiny->mesh);
    free(BOULDER_TYPES.tiny);
    AEGfxMeshFree(BOULDER_TYPES.normal->mesh);
    free(BOULDER_TYPES.normal);
    AEGfxMeshFree(BOULDER_TYPES.big->mesh);
    free(BOULDER_TYPES.big);
    AEGfxMeshFree(BOULDER_TYPES.giant->mesh);
    free(BOULDER_TYPES.giant);
}

void Boulder_onInit(Object *obj, void *data) 
{
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

void Boulder_onUpdate(Object *obj, BoulderInfo * data, float dt)
{
    UNREFERENCED_PARAMETER(dt);
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(data);
}

void Boulder_onDraw(Object *obj, BoulderInfo * data)
{
    ImageHandler_drawTexture(data->mesh, data->texture, Object_getPos(obj), 0);
}

Object * Boulder_new(BoulderInfo * type, AEVec2 pos)
{
    Object *boulder = Object_new(Boulder_onInit, Boulder_onUpdate, Boulder_onDraw, type, NULL, "Boulder");
    Object_setPos(boulder, pos);
    return boulder;
}
