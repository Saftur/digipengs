/**
 * @file ImageHandler.c
 * @author Parker Friedland
 * @date 2019/01/10
 * @brief Imports images from a filename. The file should be located in the 'Assets' folder.
 */

#pragma once

#include "ImageHandler.h"
#include "Object.h"

#define CHAR_HEIGHT 42
#define CHAR_WIDTH 23

#define SPRITESOURCE_ROWS 6
#define SPRITESOURCE_COLUMNS 16

AEGfxVertexList* getCharMesh();

AEVec2 asciiValueToOffset(char character);

Object* Text_new(char* text, AEGfxTexture* font, AEVec2 textPos, float charWidth, float charHeight, Color textColor);