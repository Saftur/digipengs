/**
 * @file Object.h
 * @author Arthur Bouvier
 * @brief Game Object
 */
#pragma once

typedef void(*ObjInit)();   ///< @brief Object init function type
typedef void(*ObjUpdate)(); ///< @brief Object update function type

/**
 * @brief Game Object
 */
typedef struct Object {
	ObjInit init;     ///< @brief Object init function
	ObjUpdate update; ///< @brief Object update function
} Object;

/**
 * @brief Create new Object
 * @param init   Init function for new Object
 * @param update Update function for new Object
 * @return New Object
 */
Object *Object_new(ObjInit init, ObjUpdate update);

/**
 * @brief Delete Object
 * @param obj Object to delete
 */
void Object_delete(Object *obj);

/**
 * @brief Initialize Object
 * @param obj Object to initialize
 */
void Object_init(Object *obj);

/**
 * @brief Update Object
 * @param obj Object to Update
 */
void Object_update(Object *obj);
