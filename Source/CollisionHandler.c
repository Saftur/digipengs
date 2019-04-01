/**
 * @file CollisionHandler.c
 * @author Brand Knutson
 * @date 1/23/2019
 * @brief Handle creating and updating colliders.
 */

#include "stdafx.h"
#include "CollisionHandler.h"
#include "object.h"
#include "ImageHandler.h"
#include "MeshHandler.h"

static vector *colliders;

static void DestroyCollider(Collider *collider);

void CollisionHandler_Init()
{
    colliders = vector_new(10, NULL, DestroyCollider);
}

void CollisionHandler_Update(float dt)
{
    for (unsigned i = 0; i < vector_size(colliders); i++) {
        Collider *collider = (Collider*)vector_at(colliders, i);
        if (collider->phase > 0) collider->phase -= dt;
    }
    CollisionHandler_Check_Collisions();
}

void CollisionHandler_SetPhaseDuration(Object * obj, float duration)
{
    for (unsigned i = 0; i < vector_size(colliders); i++) {
        Collider *collider = (Collider*)vector_at(colliders, i);
        if (collider->gameObject == obj) {
            collider->phase = duration;
            return;
        }
    }
}

void CollisionHandler_Check_Collisions()
{
    for (unsigned i = 0; i < vector_size(colliders); i++) {
        for (unsigned j = i + 1; j < vector_size(colliders); j++) {
            //Colliders.
            Collider *collider1 = (Collider*)vector_at(colliders, i);
            Collider *collider2 = (Collider*)vector_at(colliders, j);

            //If both colliders are circles.
            if (collider1->type == Circle && collider2->type == Circle) {
                if (collider1->phase > 0 || collider2->phase > 0) continue;

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

                if (strcmp(Object_getName(square->gameObject), "Wall")) if (collider1->phase > 0 || collider2->phase > 0) continue;

                //Collider Positions.
                AEVec2 squarePos = Object_getPos(square->gameObject);
                AEVec2 circlePos = Object_getPos(circle->gameObject);

                AEVec2 direction;
                AEVec2Sub(&direction, &circlePos, &squarePos);
                AEVec2 rotated;
                rotated.x = direction.x * cosf(-square->angle) - direction.y * sinf(-square->angle);
                rotated.y = direction.x * sinf(-square->angle) + direction.y * cosf(-square->angle);
                
                AEVec2 test;
                AEVec2Add(&test, &squarePos, &rotated);

                //ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.screen_separator, squarePos, square->size.x, square->size.y, square->angle, 1);

                float dist = AECalcDistCircleToRect(&test, circle->radius, &squarePos, square->size.x, square->size.y);
                if (dist < circle->radius) {
                    if (square->OnCollision) square->OnCollision(square, circle);
                    if (circle->OnCollision) circle->OnCollision(circle, square);
                }
            }
        }
    }
}

void CollisionHandler_Create_Square_Collider(Object * gameObject, AEVec2 size, float angle, void(*OnCollision)(Collider *self, Collider *other))
{
    Collider *collider = malloc(sizeof(Collider));
    collider->type = Square;
    collider->gameObject = gameObject;
    collider->OnCollision = OnCollision;
    collider->size = size;
    collider->angle = angle;

    vector_push_back(colliders, collider);
}

void CollisionHandler_Create_Circle_Collider(Object * gameObject, float radius, float angle, void(*OnCollision)(Collider *self, Collider *other))
{
    Collider *collider = malloc(sizeof(Collider));
    collider->type = Circle;
    collider->gameObject = gameObject;
    collider->OnCollision = OnCollision;
    collider->radius = radius;
    collider->angle = angle;

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
