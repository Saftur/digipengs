/**
 * @file Button.h
 * @author Parker Friedland
 * @brief Example Game Object
 */
#pragma once

#include "Object.h"

/**
 * @brief Create new Button
 * @return New Button
 */
Object *Button_new(AEGfxTexture *defaultTexture, AEGfxTexture *mouseHoverTexture, AEGfxTexture *OnClickTexture, AEGfxVertexList *mesh, int x, int y);

