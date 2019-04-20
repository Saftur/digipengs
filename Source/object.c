/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Object.c
 * @author Arthur Bouvier
 * @brief Object implementation
 */
#include "stdafx.h"

#include "Object.h"
#include "CollisionHandler.h"


typedef struct Object {
    ObjInit init;                     ///< Object init function
    ObjUpdate update;                 ///< Object update function
	ObjDraw draw;	                  ///< Object draw function

    char *name;                       ///< Object name
	void *data;	                      ///< Object data
	ObjDataDestructor dataDestructor; ///< Object data destructor
	AEVec2 pos;		                  ///< Object position
} Object;

Object *Object_new(ObjInit init, ObjUpdate update, ObjDraw draw, void *data, ObjDataDestructor dataDestructor, char *name) {
	Object *obj = malloc(sizeof(Object));

	if (!obj) return NULL;
	obj->init = init;
	obj->update = update;
	obj->draw = draw;
	obj->data = data;
    obj->dataDestructor = dataDestructor;
	obj->pos.x = 0.f;
	obj->pos.y = 0.f;
    obj->name = name;

	return obj;
}

void Object_delete(Object *obj) {
	if (obj->dataDestructor)
		obj->dataDestructor(obj->data);
    CollisionHandler_Destroy_Collider_On_Object(obj);
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

void Object_draw(Object *obj) {
	if (obj->draw)
		obj->draw(obj, obj->data);
}

void *Object_getData(Object *obj) {
    return obj->data;
}

char * Object_getName(Object * obj)
{
    return obj->name;
}

AEVec2 Object_getPos(Object *obj) {
	return obj->pos;
}

void Object_setPos(Object *obj, AEVec2 pos) {
	obj->pos = pos;
}
