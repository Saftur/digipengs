/**
 * @file Object.c
 * @author Arthur Bouvier
 * @brief Object implementation
 */
#include "stdafx.h"

#include "Object.h"


typedef struct Object {
    ObjInit init;     ///< @brief Object init function
    ObjUpdate update; ///< @brief Object update function
} Object;

Object *Object_new(ObjInit init, ObjUpdate update) {
	Object *obj = malloc(sizeof(Object));

	obj->init = init;
	obj->update = update;

	return obj;
}

void Object_delete(Object *obj) {
	free(obj);
}

void Object_init(Object *obj) {
	if (obj->init)
		obj->init();
}

void Object_update(Object *obj) {
	if (obj->update)
		obj->update();
}
