/**
 * @file Object.c
 * @author Arthur Bouvier
 * @brief Object implementation
 */
#include "stdafx.h"

#include "Object.h"


typedef struct Object {
    ObjInit init;     ///< Object init function
    ObjUpdate update; ///< Object update function
	void *data;	      ///< Object data
	AEVec2 pos;		  ///< Object position
} Object;

Object *Object_new(ObjInit init, ObjUpdate update, void *data) {
	Object *obj = malloc(sizeof(Object));

	obj->init = init;
	obj->update = update;
	obj->data = data;
	obj->pos.x = 0.f;
	obj->pos.y = 0.f;

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

AEVec2 Object_getPos(Object *obj) {
	return obj->pos;
}

void Object_setPos(Object *obj, AEVec2 pos) {
	obj->pos = pos;
}
