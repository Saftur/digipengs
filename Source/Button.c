/**
 * @file Button.c
 * @author Parker Friedland
 * @brief Button implementation
 */
#include "stdafx.h"

#include "Button.h"
#include <AEEngine.h>
#include "ImageHandler.h"

typedef struct Button {
	AEGfxTexture *texture;
	AEGfxVertexList *mesh;
} Button;

/**
 * @brief Button init function
 */
void Button_onInit(Object *obj, void *data) {
	printf("Button init\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

/**
 * @brief Button update function
 */
void Button_onUpdate(Object *obj, void *data, float dt) {
	printf("Button update\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(dt);
}

void Button_onDraw(Object *obj, Button *data) {
	ImageHandler_drawTexture(data->mesh, data->texture, Object_getPos(obj), 0);
}

Object *Button_new(AEGfxTexture *texture, AEGfxVertexList *mesh, AEVec2 pos) {
	Button *buttonData = malloc(sizeof(Button));
	buttonData->texture = texture;
	buttonData->mesh = mesh;
	Object *buttonObj = Object_new(Button_onInit, Button_onUpdate, Button_onDraw, buttonData, free);
	Object_setPos(buttonObj, pos);
	return buttonObj;
}
