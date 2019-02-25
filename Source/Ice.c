/**
 * @file Ice.c
 * @author Connor Meyers
 * @brief Object implementation for the Ice obstacle
 */

#include "stdafx.h"

#include "Ice.h"

#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Object.h"

typedef float IceSize;

void Ice_onDraw(Object *obj, IceSize *size)
{
    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.test, Object_getPos(obj), *size, 0, 1.0f);
}

Object *Ice_new(AEVec2 pos)
{
    IceSize *pSize = malloc(sizeof(IceSize));
    if (!pSize)
        return NULL;
    *pSize = (float)ICE_DEFAULT_SIZE;
    Object *ice = Object_new(NULL, NULL, Ice_onDraw, pSize, free, "Ice");
    Object_setPos(ice, pos);
    return ice;
}


void Ice_decrementSize(Object* ice)
{
    *((IceSize*)Object_getData(ice)) -= (float)ICE_DECREMENT;
}

void Ice_incrementSize(Object* ice)
{
    *((IceSize*)Object_getData(ice)) += (float)ICE_INCREMENT;
}
