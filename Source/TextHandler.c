/**
 * @file ImageHandler.c
 * @author Parker Friedland
 * @date 2019/01/10
 * @brief Imports images from a filename. The file should be located in the 'Assets' folder.
 */

#include "stdafx.h"		// Should be included first in every .c file!

#include "TextHandler.h"
#include "MeshHandler.h"
#include "ImageHandler.h"
#include "objectmanager.h"

typedef struct Character {
	char character;
	AEGfxVertexList *charMesh;
	AEGfxTexture *font;
	AEVec2 textPos;
	f32 offsetX;
	f32 offsetY;
	float width;
	float height;
} Character;

void Char_onInit(Object *obj, void *data) 
{
	printf("Char init\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}


void Char_onUpdate(Object *obj, Character *data, float dt) 
{
	printf("Char update\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(dt);
}

void Char_onDraw(Object *obj, Character *data)
{
	ImageHandler_screenDrawTextureWithOffset(data->charMesh, data->font, Object_getPos(obj), CHAR_WIDTH, CHAR_HEIGHT, 0, 1, data->offsetX, data->offsetY);
}

AEGfxVertexList* createCharMesh()
{
	return MeshHandler_createSquareMesh(0.5f, 0.5f, 1.0f / TEXT_COLUMNS, 1.0f / TEXT_ROWS);
}

AEVec2 asciiValueToOffset(char character)
{
	int row = ((int) (character - ' ')) / TEXT_COLUMNS;
	int column = ((int) (character - ' ')) % TEXT_COLUMNS;
	AEVec2 offset = { 0,0 };
	offset.x = ((f32) (column)) / ((f32) (TEXT_COLUMNS));
	offset.y = ((f32) (row)) / ((f32) (TEXT_ROWS));
	
	return offset;
}

void createCharacters(char *text, AEGfxTexture *font, AEVec2 textPos, float charWidth, float charHeight)
{
	AEGfxVertexList *charMesh = createCharMesh();
	AEVec2 charOffset;

	for(int i = 0; i < text[i] != '\0'; i++)
	{
		if (text[i] == '\n')
		{
			textPos.y -= CHAR_HEIGHT;
		}
		else
		{
			charOffset = asciiValueToOffset(text[i]);

			Character *charData = malloc(sizeof(Character));
			charData->character = text[i];
			charData->charMesh = charMesh;
			charData->font = font;
			charData->textPos = textPos;
			charData->offsetX = charOffset.x;
			charData->offsetY = charOffset.y;
			charData->width = charWidth;
			charData->height = charHeight;

			Object *charObj = Object_new(Char_onInit, Char_onUpdate, Char_onDraw, charData, free, "Character");
			Object_setPos(charObj, textPos);
			ObjectManager_addObj(charObj);

			textPos.x += CHAR_WIDTH;
		}
	}
}