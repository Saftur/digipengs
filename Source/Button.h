/**
 * @file Button.h
 * @author Arthur Bouvier
 * @brief Example Game Object
 */
#pragma once

#include "Object.h"

/**
 * @brief Create new Button
 * @return New Button
 */
Object *Button_new(AEGfxTexture *texture, AEGfxVertexList *mesh);
