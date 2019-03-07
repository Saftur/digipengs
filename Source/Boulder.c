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

typedef float BoulderSize;

void Boulder_onDraw(Object *obj, BoulderSize *size)
{
    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.boulder, Object_getPos(obj), *size, *size, 0, 1.0f);
}

Object *Boulder_new(AEVec2 pos)
{
    BoulderSize *pSize = malloc(sizeof(BoulderSize));
    if (!pSize)
        return NULL;
    *pSize = (float)BOULDER_DEFAULT_SIZE;
    Object *boulder = Object_new(NULL, NULL, Boulder_onDraw, pSize, free, "Boulder");
    Object_setPos(boulder, pos);
    return boulder;
}


void Boulder_decrementSize(Object* boulder)
{
    *((BoulderSize*)Object_getData(boulder)) -= (float)BOULDER_DECREMENT;
}

void Boulder_incrementSize(Object* boulder)
{
    *((BoulderSize*)Object_getData(boulder)) += (float)BOULDER_INCREMENT;
}
