/**
 * @file CollisionEvents.c
 * @author Brand Knutson
 * @date 1/23/2019
 * @brief All OnCollision functions.
 */

#pragma once
#include "CollisionHandler.h"
#include "Player.h"

 /**
  * @brief Player OnCollision function.
  * @param self  The collider for this object.
  * @param other The other collider that this object hit.
  */
void PlayerOnCollision(Collider *self, Collider *other);

void StartLineOnCollision(Collider *self, Collider *other);
void CheckpointOnCollision(Collider *self, Collider *other);