/**
 * @file Button.c
 * @author Parker Friedland
 * @brief Button implementation
 */
#include "stdafx.h"
#include "ImageHandler.h"
#include "Button.h"
#include <AEEngine.h>

typedef struct Button {
	AEGfxTexture *defaultTexture;
	AEGfxTexture *mouseHoverTexture;
	AEGfxTexture *OnClickTexture;
	AEGfxVertexList *mesh;
	//what to do when pressed
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
	ImageHandler_drawTexture(data->mesh, data->defaultTexture, Object_getPos(obj));
}

Object *Button_new(AEGfxTexture *defaultTexture, AEGfxTexture *mouseHoverTexture, AEGfxTexture *OnClickTexture, AEGfxVertexList *mesh, int x, int y) {
	Button *buttonData = malloc(sizeof(Button));
	buttonData->defaultTexture = defaultTexture;
	buttonData->mouseHoverTexture = mouseHoverTexture;
	buttonData->OnClickTexture = OnClickTexture;
	buttonData->mesh = mesh;
	Object *buttonObj = Object_new(Button_onInit, Button_onUpdate, Button_onDraw, buttonData);
	Object_setPos(buttonObj, (AEVec2) { x, y });
	ObjectManager_addObj(buttonObj);
	return buttonObj;
}
