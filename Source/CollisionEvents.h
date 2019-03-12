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
  * @brief Example OnCollision function.
  * @param self The collider for this object.
  * @param other The other collider that this object hit.
  */
void DoNothingOnCollision(Collider *self, Collider *other);

void PlayerOnCollision(Collider *self, Collider *other);