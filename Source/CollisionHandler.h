/**
 * @file CollisionHandler.h
 * @author Brand Knutson
 * @date 1/23/2019
 * @brief Handle creating and updating colliders.
 */

#pragma once
#include "AEVec2.h"
#include "object.h"
#include "vector.h"


typedef enum { Square, Circle } ColliderType;

typedef struct Collider Collider;

typedef struct Collider {

    AEVec2 size; ///< Size of the collider when type is Square.
    float radius; ///< Radius of the collider when type is Circle.
    ColliderType type; ///< The type of the collider.

    void(*OnCollision)(Collider *self, Collider *other); ///< Function to be called when a collision is detected.

    Object *gameObject; ///< GameObject that this collider is attatched to.
} Collider;

/**
 * @brief Initialize the collision handler.
 */
void CollisionHandler_Init();

/**
 * @brief Check collisions between all colliders.
 */
void CollisionHandler_Check_Collisions();

/**
 * @brief Create a square collider.
 * @param gameObject Pointer to the gameobject to attatch the collider to.
 * @param size Size of the collider.
 * @param OnCollision Function pointer to be called on collision.
 */
void CollisionHandler_Create_Square_Collider(Object *gameObject, AEVec2 size, void(*OnCollision)(Collider *self, Collider *other));

/**
 * @brief Create a circle collider.
 * @param gameObject Pointer to the gameobject to attatch the collider to.
 * @param radius Radius of the collider.
 * @param OnCollision Function pointer to be called on collision.
 */
void CollisionHandler_Create_Circle_Collider(Object *gameObject, float radius, void(*OnCollision)(Collider *self, Collider *other));

/**
 * @brief Destroy a collider.
 * @param collider to destroy.
 */
void CollisionHandler_Destroy_Collider(Collider *collider);

/**
 * @brief Destroy a collider on an object.
 * @param object What object to remove a collider from.
 */
void CollisionHandler_Destroy_Collider_On_Object(Object *object);