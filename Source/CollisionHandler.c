/**
 * @file CollisionHandler.c
 * @author Brand Knutson
 * @date 1/23/2019
 * @brief Handle creating and updating colliders.
 */

#include "stdafx.h"
#include "CollisionHandler.h"
#include "object.h"

static vector *colliders;

static void DestroyCollider(Collider *collider);

void CollisionHandler_Init()
{
    colliders = vector_new(10, NULL, DestroyCollider);
}

void CollisionHandler_Check_Collisions()
{
    for (unsigned i = 0; i < vector_size(colliders) - 1; i++) {
        for (unsigned j = i + 1; j < vector_size(colliders); i++) {
            //Colliders.
            Collider *collider1 = (Collider*)vector_at(colliders, i);
            Collider *collider2 = (Collider*)vector_at(colliders, j);

            //If both colliders are circles.
            if (collider1->type == Circle && collider2->type == Circle) {
                //Colliders positions.
                AEVec2 pos1 = Object_getPos(collider1->gameObject);
                AEVec2 pos2 = Object_getPos(collider2->gameObject);

                //Find distance between colliders.
                AEVec2 distance;
                distance.x = pos2.x - pos1.x;
                distance.y = pos2.y - pos1.y;
                float dist = sqrtf(distance.x * distance.x + distance.y * distance.y);

                //If colliders are colliding.
                if (dist <= collider1->radius + collider2->radius) {
                    if(collider1->OnCollision) collider1->OnCollision(collider1, collider2);
                    if(collider2->OnCollision) collider2->OnCollision(collider2, collider1);
                }
            }
            //If both colliders are squares.
            else if (collider1->type == Square && collider2->type == Square) {

            }
            //If one collider is a circle, and the other is a square.
            else {
                //Determine which collider is which.
                Collider *square = collider1->type == Square ? collider1 : collider2;
                Collider *circle = collider1->type == Circle ? collider1 : collider2;

                //Collider Positions.
                AEVec2 squarePos = Object_getPos(square->gameObject);
                AEVec2 circlePos = Object_getPos(circle->gameObject);

                //Get direction towards the square collider.
                AEVec2 direction;
                direction.x = squarePos.x - circlePos.x;
                direction.y = squarePos.y - circlePos.y;
                AEVec2Normalize(&direction, &direction);

                //Point to determine if is inside of the square or not.
                AEVec2 point;
                AEVec2Add(&point, &direction, &circlePos);

                //If colliders are colliding.
                if (point.x >= squarePos.x && point.y < squarePos.x + square->size.x && point.y >= squarePos.y && point.y < squarePos.y + square->size.y) {
                    if(square->OnCollision) square->OnCollision(square, circle);
                    if(circle->OnCollision) circle->OnCollision(circle, square);
                }
            }
        }
    }
}

void CollisionHandler_Create_Square_Collider(Object * gameObject, AEVec2 size, void(*OnCollision)(Collider *self, Collider *other))
{
    Collider *collider = malloc(sizeof(Collider));
    collider->type = Square;
    collider->gameObject = gameObject;
    collider->OnCollision = OnCollision;
    collider->size = size;

    vector_push_back(colliders, collider);
}

void CollisionHandler_Create_Circle_Collider(Object * gameObject, float radius, void(*OnCollision)(Collider *self, Collider *other))
{
    Collider *collider = malloc(sizeof(Collider));
    collider->type = Circle;
    collider->gameObject = gameObject;
    collider->OnCollision = OnCollision;
    collider->radius = radius;

    vector_push_back(colliders, collider);
}

void CollisionHandler_Destroy_Collider(Collider * collider)
{
    for (unsigned i = 0; i < vector_size(colliders); i++) {
        if (vector_at(colliders, i) == collider) {
            vector_erase(colliders, i);
            return;
        }
    }
}

void CollisionHandler_Destroy_Collider_On_Object(Object * object)
{
    for (unsigned i = 0; i < vector_size(colliders); i++) {
        if (((Collider*)vector_at(colliders, i))->gameObject == object) {
            vector_erase(colliders, i);
            return;
        }
    }
}

static void DestroyCollider(Collider *collider) {
    free(collider);
}
