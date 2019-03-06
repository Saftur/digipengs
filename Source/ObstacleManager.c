/**
 * @file ObstacleManager.c
 * @author Brand Knutson
 * @date 2/25/2019
 * @brief Load obstacles onto the map.
 */

#include "stdafx.h"
#include "ObstacleManager.h"
#include "Boulder.h"
#include "Polarbear.h"
#include "Ice.h"
#include "Pothole.h"
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
            obstacle = Boulder_new(obstacleData->pos);
            Boulder_setSize(obstacle, obstacleData->radius * 2);
            CollisionHandler_Create_Circle_Collider(obstacle, obstacleData->radius, NULL);
            break;
        case 'P':
            obstacle = Polarbear_new(obstacleData->pos);
            Polarbear_setSize(obstacle, obstacleData->radius * 2);
            CollisionHandler_Create_Circle_Collider(obstacle, obstacleData->radius, NULL);
            break;
        case 'I':
            obstacle = Ice_new(obstacleData->pos);
            Ice_setSize(obstacle, obstacleData->radius * 2);
            CollisionHandler_Create_Circle_Collider(obstacle, obstacleData->radius, NULL);
            break;
        }

        ObjectManager_addObj(obstacle);
    }
    fclose(file);
}
