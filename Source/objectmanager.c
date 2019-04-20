/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file ObjectManager.c
 * @author Arthur Bouvier
 * @brief ObjectManager implementation
 */
#include "stdafx.h"

#include "ObjectManager.h"
#include "vector.h"

static vector *objs;

void ObjectManager_init() {
	objs = vector_new(10, NULL, Object_delete);
}

void ObjectManager_update(float dt) {
	for (unsigned i = 0; i < vector_size(objs); i++) {
		Object *obj = vector_at(objs, i);

		Object_update(obj, dt);
	}
}

void ObjectManager_draw() {
	for (unsigned i = 0; i < vector_size(objs); i++) {
		Object *obj = vector_at(objs, i);

		Object_draw(obj);
	}
}

void ObjectManager_addObj(Object *obj) {
	Object_init(obj);
	vector_push_back(objs, obj);
}

void ObjectManager_delObj(Object * obj) {
    for (unsigned i = 0; i < vector_size(objs); i++) {
        if (vector_at(objs, i) == obj)
            vector_erase(objs, i);
    }
}

size_t ObjectManager_numObjs() {
    return vector_size(objs);
}

Object *ObjectManager_getObj(unsigned i) {
    return vector_at(objs, i);
}

void ObjectManager_reset() {
    vector_clear(objs);
}

void ObjectManager_shutdown() {
	vector_delete(objs);
}
