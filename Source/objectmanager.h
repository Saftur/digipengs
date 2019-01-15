/**
 * @file ObjectManager.h
 * @author Arthur Bouvier
 * @brief Game Object manager
 */
#pragma once

#include "Object.h"

/**
 * @brief Initialize ObjectManager
 */
void ObjectManager_init();

/**
 * @brief Update ObjectManager
 */
void ObjectManager_update();

/**
 * @brief Add Object to ObjectManager
 * @param obj Object to add
 */
void ObjectManager_addObj(Object *obj);

/**
 * @brief End ObjectManager
 */
void ObjectManager_end();
