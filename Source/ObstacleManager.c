/**
 * @file ObstacleManager.c
 * @author Brand Knutson
 * @date 2/25/2019
 * @brief Load obstacles onto the map.
 */

#include "stdafx.h"
#include "ObstacleManager.h"
#include "Boulder.h"
#include "objectmanager.h"
#include "CollisionHandler.h"
#include "Object.h"
#include "CollisionEvents.h"
#include "ImageHandler.h"
#include "MeshHandler.h"

static void ObstacleDraw(Object *object, Obstacle *data);

void ObstacleManager_loadObstacles()
{
    FILE *file;
    fopen_s(&file, "./Assets/ObstacleMap.txt", "rt");
    if (!file) return;

    Obstacle *obstacleData = malloc(sizeof(Obstacle));
    Object *obstacle = NULL;
    char obstacleType;
    while ((obstacleType = (char)fgetc(file)) != EOF) {
        obstacleData = malloc(sizeof(Obstacle));
        char locString[6];
        locString[5] = '\0';

        obstacleData->radius = (float)atoi(fgets(locString, 6, file));
        obstacleData->pos.x = (float)atoi(fgets(locString, 6, file));
        obstacleData->pos.y = (float)atoi(fgets(locString, 6, file));
        obstacleData->rotation = (float)atoi(fgets(locString, 6, file));

        switch (obstacleType) {
        case 'B':
            obstacleData->type = Boulder;
            obstacle = Object_new(NULL, NULL, ObstacleDraw, obstacleData, free, "Boulder");
            Object_setPos(obstacle, obstacleData->pos);
            CollisionHandler_Create_Circle_Collider(obstacle, obstacleData->radius, NULL);
            break;
        }

        ObjectManager_addObj(obstacle);
    }
    fclose(file);
}

void ObstacleDraw(Object *object, Obstacle *data)
{
    UNREFERENCED_PARAMETER(object);

    switch (data->type) {
    case Boulder:
        ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.boulder, data->pos, data->radius * 2, data->rotation, 1);
        break;
    }
}
