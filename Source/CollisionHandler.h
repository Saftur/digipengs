/**
 * Project: DigitalPenguins
 * All content � 2019 DigiPen (USA) Corporation, all rights reserved.
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
    float phase; ///< If greater than 0 phase for this amount of time.
    float angle; ///< Rotation for the collider.

    void(*OnCollision)(Collider *self, Collider *other); ///< Function to be called when a collision is detected.

    Object *gameObject; ///< GameObject that this collider is attatched to.
} Collider;

/**
 * @brief Initialize the collision handler.
 */
void CollisionHandler_Init();

/**
 * @brief Update the collision handler.
 * @param dt DeltaTime
 */
void CollisionHandler_Update(float dt);

/**
 * @brief Set colliders phase duration.
 * @param obj Object to phase.
 * @param duration How long to phase the object for.
 */
void CollisionHandler_SetPhaseDuration(Object *obj, float duration);

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
void CollisionHandler_Create_Square_Collider(Object *gameObject, AEVec2 size, float angle, void(*OnCollision)(Collider *self, Collider *other));

/**
 * @brief Create a circle collider.
 * @param gameObject Pointer to the gameobject to attatch the collider to.
 * @param radius Radius of the collider.
 * @param OnCollision Function pointer to be called on collision.
 */
Collider *CollisionHandler_Create_Circle_Collider(Object *gameObject, float radius, float angle, void(*OnCollision)(Collider *self, Collider *other));

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
