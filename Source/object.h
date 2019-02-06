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
typedef void(*ObjDraw)(Object *obj, void *data);			 ///< Object draw function type
typedef void(*ObjDataDestructor)(void *data);				 ///< Object data destructor function type

/**
 * @brief Create new Object
 * @param init           Init function for new Object
 * @param update         Update function for new Object
 * @param draw           Draw function for new Object
 * @param data           Upvalue for Object functions
 * @param dataDestructor Upvalue destructor
 * @return New Object
 */
Object *Object_new(ObjInit init, ObjUpdate update, ObjDraw draw, void *data, ObjDataDestructor dataDestructor, char *name);

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
 * @param obj Object to update
 * @param dt Current delta time in seconds
 */
void Object_update(Object *obj, float dt);

/**
 * @brief Draw Object
 * @param obj Object to draw
 */
void Object_draw(Object *obj);

/**
 * @brief Get data pointer from Object
 * @param obj Object to get from
 * @return Data pointer
 */
void *Object_getData(Object *obj);

/**
 * @brief Get name from Object
 * @param obj Object to get from
 * @return Char Pointer.
 */
char *Object_getName(Object *obj);

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
