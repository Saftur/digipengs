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
    Color textColor;
	unsigned camNum;
} Text;

static void Text_onInit(Object *obj, Text *data)
{
	printf("Text init\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

static void Text_onUpdate(Object *obj, Text *data, float dt)
{
	printf("Text update\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(dt);
}

static void Text_onDraw(Object *obj, Text *data)
{
    UNREFERENCED_PARAMETER(obj);
	AEVec2 charPos, charOffset;
	charPos.x = data->textPos.x;
	charPos.y = data->textPos.y;

	for (int i = 0; i < data->text[i] != '\0'; i++)
	{
		if (data->text[i] == '\n')
		{
			charPos.y -= data->charHeight;
            charPos.x = data->textPos.x;
		}
		else
		{
			charOffset = asciiValueToOffset(data->text[i]);
            ImageHandler_setBlendColor(data->textColor);
			ImageHandler_screenDrawTextureWithOffset(getCharMesh(), data->font, charPos, data->charWidth, data->charHeight, 0, 1, charOffset.x, charOffset.y);
            ImageHandler_disableBlendColor();

			charPos.x += data->charWidth;
		}
	}
}

Object* Text_new(char *text, AEGfxTexture *font, AEVec2 textPos, float charWidth, float charHeight, Color textColor, unsigned camNum)
{
	Text* textData = malloc(sizeof(Text));
	textData->text = text;
	textData->font = font;
	textData->textPos = textPos;
	textData->charWidth = charWidth;
	textData->charHeight = charHeight;
    textData->textColor = textColor;
	textData->camNum = camNum;
	
	Object* textObj = Object_new(Text_onInit, Text_onUpdate, Text_onDraw, textData, free, "Text");
	Object_setPos(textObj, textPos);
	return textObj;
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
