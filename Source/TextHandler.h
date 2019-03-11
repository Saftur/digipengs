/**
 * @file ImageHandler.c
 * @author Parker Friedland
 * @date 2019/01/10
 * @brief Imports images from a filename. The file should be located in the 'Assets' folder.
 */

#pragma once

#include "ImageHandler.h"

#define CHAR_HEIGHT 42
#define CHAR_WIDTH 23

#define TEXT_ROWS 6
#define TEXT_COLUMNS 16

AEGfxVertexList* createCharMesh();

AEVec2 asciiValueToOffset(char character);

void createCharacters(char *text, AEGfxTexture *font, AEVec2 textPos, float width, float height);