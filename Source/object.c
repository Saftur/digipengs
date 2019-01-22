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
	void *data;	      ///< @brief Object data
} Object;

Object *Object_new(ObjInit init, ObjUpdate update, void *data) {
	Object *obj = malloc(sizeof(Object));

	obj->init = init;
	obj->update = update;
	obj->data = data;

	return obj;
}

void Object_delete(Object *obj) {
	free(obj->data);
	free(obj);
}

void Object_init(Object *obj) {
	if (obj->init)
		obj->init(obj, obj->data);
}

void Object_update(Object *obj, float dt) {
	if (obj->update)
		obj->update(obj, obj->data, dt);
}
