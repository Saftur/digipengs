/**
 * @file ObjectManager.c
 * @author Arthur Bouvier
 * @brief ObjectManager implementation
 */
#include "stdafx.h"

#include "ObjectManager.h"
#include "vector.h"

static vector *objs;

void ObjectManager_init() {
	objs = vector_new(10);
}

void ObjectManager_update(float dt) {
	for (unsigned i = 0; i < vector_size(objs); i++) {
		Object *obj = vector_at(objs, i);

		Object_update(obj, dt);
	}
}

void ObjectManager_addObj(Object *obj) {
	Object_init(obj);
	vector_push_back(objs, obj);
}

void ObjectManager_end() {
	vector_delete(objs);
}
