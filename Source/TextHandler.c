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

AEGfxVertexList* charMesh = NULL;

typedef struct Text {
	char* text;
	AEGfxTexture *font;
	AEVec2 textPos;
	float charWidth;
	float charHeight;
} Text;

Object* Text_new(char *text, AEGfxTexture *font, AEVec2 textPos, float charWidth, float charHeight)
{
	Text *textData = malloc(sizeof(Text));
	textData->text = text;
	textData->font = font;
	textData->textPos = textPos;
	textData->charWidth = charWidth;
	textData->charHeight = charHeight;
	
	Object *textObj = Object_new(Text_onInit, Text_onUpdate, Text_onDraw, textData, free, "Text");
	Object_setPos(textObj, textPos);
	ObjectManager_addObj(textObj);
	return textObj;
}

void Text_onInit(Object *obj, Text *data)
{
	printf("Text init\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

void Text_onUpdate(Object *obj, Text *data, float dt)
{
	printf("Text update\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(dt);
}

void Text_onDraw(Object *obj, Text *data)
{
	AEVec2 charPos, charOffset;
	charPos.x = data->textPos.x;
	charPos.y = data->textPos.y;

	for (int i = 0; i < data->text[i] != '\0'; i++)
	{
		if (data->text[i] == '\n')
		{
			charPos.y -= CHAR_HEIGHT;
		}
		else
		{
			charOffset = asciiValueToOffset(data->text[i]);
			ImageHandler_screenDrawTextureWithOffset(getCharMesh(), data->font, charPos, CHAR_WIDTH, CHAR_HEIGHT, 0, 1, charOffset.x, charOffset.y);

			charPos.x += CHAR_WIDTH;
		}
	}
}

AEVec2 asciiValueToOffset(char character)
{
	int row = ((int)(character - ' ')) / SPRITESOURCE_COLUMNS;
	int column = ((int)(character - ' ')) % SPRITESOURCE_COLUMNS;
	AEVec2 offset = { 0,0 };
	offset.x = ((f32)(column)) / ((f32)(SPRITESOURCE_COLUMNS));
	offset.y = ((f32)(row)) / ((f32)(SPRITESOURCE_ROWS));

	return offset;
}

AEGfxVertexList* getCharMesh()
{
	if (charMesh == NULL)
	{
		charMesh = MeshHandler_createSquareMesh(0.5f, 0.5f, 1.0f / SPRITESOURCE_COLUMNS, 1.0f / SPRITESOURCE_ROWS);
	}
	return charMesh;
}