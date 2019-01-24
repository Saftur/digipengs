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

static void initalizeInfo(BoulderInfoPtr * info, AEGfxTexture *texture, float size)
{
    *info = (BoulderInfoPtr)malloc(sizeof(BoulderInfo));
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
    free(BOULDER_TYPES.tiny);
    free(BOULDER_TYPES.normal);
    free(BOULDER_TYPES.big);
    free(BOULDER_TYPES.giant);
}

void Boulder_onInit(Object *obj, void *data) 
{
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

float rotation = 0;
void Boulder_onUpdate(Object *obj, void *data, float dt) 
{
    BoulderInfo infoData = *(BoulderInfoPtr)data;
    UNREFERENCED_PARAMETER(dt);

    ImageHandler_drawTexture(infoData.mesh, infoData.texture, Object_getPos(obj));
}

Object * Boulder_new(BoulderInfoPtr type, AEVec2 pos)
{
    BoulderInfoPtr data = (BoulderInfoPtr)malloc(sizeof(BoulderInfo));
    memcpy(data, type, sizeof(BoulderInfo));
    Object *boulder = Object_new(Boulder_onInit, Boulder_onUpdate, type);
    Object_setPos(boulder, pos);
    return boulder;
}
