/**
 * @file Object.h
 * @author Arthur Bouvier
 * @brief Game Object
 */
#pragma once

#include <AEEngine.h>

/**
 * @brief Game Object
 */
typedef struct Object Object;

typedef void(*ObjInit)(Object *obj, void *data);			 ///< Object init function type
typedef void(*ObjUpdate)(Object *obj, void *data, float dt); ///< Object update function type

/**
 * @brief Create new Object
 * @param init   Init function for new Object
 * @param update Update function for new Object
 * @param data   Upvalue for Object functions
 * @return New Object
 */
Object *Object_new(ObjInit init, ObjUpdate update, void *data);

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
 * @param dt Current delta time in seconds
 */
void Object_update(Object *obj, float dt);

/**
 * @brief Get Object position
 * @param obj Object to get from
 * @return Position of Object
 */
AEVec2 Object_getPos(Object *obj);

/**
 * @brief Set Object position
 * @param obj Object to set on
 * @param pos New position
 */
void Object_setPos(Object *obj, AEVec2 pos);
