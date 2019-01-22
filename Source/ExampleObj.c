/**
 * @file ExampleObj.c
 * @author Arthur Bouvier
 * @brief ExampleObj implementation
 */
#include "stdafx.h"

#include "ExampleObj.h"

/**
 * @brief ExampleObj init function
 */
void ExampleObj_onInit(Object *obj, void *data) {
	printf("ExampleObj init\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

/**
 * @brief ExampleObj update function
 */
void ExampleObj_onUpdate(Object *obj, void *data, float dt) {
	printf("ExampleObj update\n");
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(dt);
}

Object *ExampleObj_new() {
	return Object_new(ExampleObj_onInit, ExampleObj_onUpdate, NULL);
}
