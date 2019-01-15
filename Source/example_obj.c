/**
 * @file example_obj.c
 * @author Arthur Bouvier
 * @brief ExampleObj implementation
 */
#include "stdafx.h"

#include "example_obj.h"

/**
 * @brief ExampleObj init function
 */
void ExampleObj_onInit() {
	printf("ExampleObj init\n");
}

/**
 * @brief ExampleObj update function
 */
void ExampleObj_onUpdate() {
	printf("ExampleObj update\n");
}

Object *ExampleObj_new() {
	return Object_new(ExampleObj_onInit, ExampleObj_onUpdate);
}
