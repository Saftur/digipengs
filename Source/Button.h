/**
 * @file Button.h
 * @author Parker Friedland
 * @brief Example Game Object
 */
#pragma once

#include "Object.h"

#define DEFAULT 0
#define HOVER 1
#define ON_CLICK 2

typedef void(*ButtonEffectFunc)();

/**
 * @brief Create new Button
 * @return New Button
 */
Object *Button_new(ButtonEffectFunc buttonEffect, AEGfxTexture *defaultTexture, AEGfxTexture *mouseHoverTexture, AEGfxTexture *onClickTexture,
	float x, float y, float width, float height);