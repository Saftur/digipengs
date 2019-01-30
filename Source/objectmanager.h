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
 * @param dt Current delta time in seconds
 */
void ObjectManager_update(float dt);

/**
 * @brief Draw ObjectManager
 */
void ObjectManager_draw();

/**
 * @brief Add Object to ObjectManager
 * @param obj Object to add
 */
void ObjectManager_addObj(Object *obj);

/**
 * @brief Shutdown ObjectManager
 */
void ObjectManager_shutdown();
