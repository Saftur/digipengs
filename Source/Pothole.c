/**
 * @file Pothole.c
 * @author Connor Meyers
 * @brief Object implementation for the pothole obstacle
 */

#include "stdafx.h"

#include "Pothole.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Object.h"

typedef float PotholeSize;

void Pothole_onDraw(Object *obj, PotholeSize *size)
{
    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.player, Object_getPos(obj), *size, 0, 1.0f);
}

Object *Pothole_new(AEVec2 pos)
{
    PotholeSize *pSize = malloc(sizeof(PotholeSize));
    *pSize = (float)POTHOLE_DEFAULT_SIZE;
    if (!pSize)
        return NULL;
    Object *pothole = Object_new(NULL, NULL, Pothole_onDraw, pSize, free, "Pothole");
    Object_setPos(pothole, pos);
    return pothole;
}


void Pothole_decrementSize(Object* pothole)
{
    *((PotholeSize*)Object_getData(pothole)) -= (float)POTHOLE_DECREMENT;
}

void Pothole_incrementSize(Object* pothole)
{
    *((PotholeSize*)Object_getData(pothole)) += (float)POTHOLE_INCREMENT;
}
