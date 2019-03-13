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
#include "Map.h"

#define NUM_WALLS 8

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
        obstacleData->rotation = AEDegToRad((float)atoi(fgets(locString, 6, file)));

        switch (obstacleType) {
        case 'B':
            obstacle = Boulder_new(obstacleData->pos);
            Boulder_setSize(obstacle, obstacleData->radius * 2);
            CollisionHandler_Create_Circle_Collider(obstacle, obstacleData->radius, obstacleData->rotation, NULL);
            break;
        case 'P':
            obstacle = Polarbear_new(obstacleData->pos);
            Polarbear_setSize(obstacle, obstacleData->radius * 2);
            CollisionHandler_Create_Circle_Collider(obstacle, obstacleData->radius, obstacleData->rotation, NULL);
            break;
        case 'I':
            obstacle = Ice_new(obstacleData->pos);
            Ice_setSize(obstacle, obstacleData->radius * 2);
            CollisionHandler_Create_Circle_Collider(obstacle, obstacleData->radius, obstacleData->rotation, NULL);
            break;
        }

        ObjectManager_addObj(obstacle);
    }
    fclose(file);

    //Build walls on the map.
    AEVec2 tileWorldPos;
    unsigned tileX = Map_getStartX(), tileY = Map_getStartY();

    unsigned initialTileX = tileX, initialTileY = tileY;

    do {
        Map_tilePosToWorldPos(&tileWorldPos.x, &tileWorldPos.y, tileX, tileY);
        Tile tile = Map_getTile(tileX, tileY);

        //If the tile is a straight segment.
        if (tile.from == SDown && tile.to == SUp || tile.from == SUp && tile.to == SDown
            || tile.from == SLeft && tile.to == SRight || tile.from == SRight && tile.to == SLeft) {
            //Get the position to create the wall at.
            AEVec2 wallPos;

            if (tile.to == SRight || tile.to == SLeft) {
                wallPos.y = tileWorldPos.y + (LANE_WIDTH * 3);
                wallPos.x = tileWorldPos.x;

                Object *wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                Object_setPos(wall, wallPos);

                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { TILE_SIZE, LANE_WIDTH / 2 }, 0, NULL);
                ObjectManager_addObj(wall);

                wallPos.y = tileWorldPos.y - (LANE_WIDTH * 3);
                wallPos.x = tileWorldPos.x;

                wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                Object_setPos(wall, wallPos);

                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { TILE_SIZE, LANE_WIDTH / 2 }, 0, NULL);
                ObjectManager_addObj(wall);
            }
            else {
                wallPos.x = tileWorldPos.x + (LANE_WIDTH * 3);
                wallPos.y = tileWorldPos.y;

                Object *wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                Object_setPos(wall, wallPos);

                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { LANE_WIDTH / 2, TILE_SIZE }, 0, NULL);
                ObjectManager_addObj(wall);

                wallPos.x = tileWorldPos.x - (LANE_WIDTH * 3);
                wallPos.y = tileWorldPos.y;

                wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                Object_setPos(wall, wallPos);

                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { LANE_WIDTH / 2, TILE_SIZE }, 0, NULL);
                ObjectManager_addObj(wall);
            }
        }
        //Corner tile.
        else {
            AEVec2 wallPos[NUM_WALLS];
            float wallRot[NUM_WALLS];

            float angleInc = PI / 2.f / NUM_WALLS;
            for (unsigned i = 0; i < NUM_WALLS; i++) wallRot[i] = ((float)i + 0.5f) * angleInc;

            AEVec2 point = {0, 0};
            if ((tile.from == SDown && tile.to == SRight) || (tile.from == SRight && tile.to == SDown)) {
                point.x = tileWorldPos.x + TILE_SIZE / 2.f;
                point.y = tileWorldPos.y - TILE_SIZE / 2.f;

                for (unsigned i = 0; i < NUM_WALLS; i++) {
                    wallRot[i] += PI / 2.f;
                    wallPos[i].x = point.x + cosf(wallRot[i]) * (TILE_SIZE - LANE_WIDTH / 2);
                    wallPos[i].y = point.y + sinf(wallRot[i]) * (TILE_SIZE - LANE_WIDTH / 2);
                }
            }
            else if ((tile.from == SLeft && tile.to == SDown) || (tile.from == SDown && tile.to == SLeft)) {
                point.x = tileWorldPos.x - TILE_SIZE / 2.f;
                point.y = tileWorldPos.y - TILE_SIZE / 2.f;

                for (unsigned i = 0; i < NUM_WALLS; i++) {
                    wallPos[i].x = point.x + cosf(wallRot[i]) * (TILE_SIZE - LANE_WIDTH / 2);
                    wallPos[i].y = point.y + sinf(wallRot[i]) * (TILE_SIZE - LANE_WIDTH / 2);
                }
            }
            else if ((tile.from == SUp && tile.to == SLeft) || (tile.from == SLeft && tile.to == SUp)) {
                point.x = tileWorldPos.x - TILE_SIZE / 2.f;
                point.y = tileWorldPos.y + TILE_SIZE / 2.f;

                for (unsigned i = 0; i < NUM_WALLS; i++) {
                    wallRot[i] += PI * 1.5f;
                    wallPos[i].x = point.x + cosf(wallRot[i]) * (TILE_SIZE - LANE_WIDTH / 2);
                    wallPos[i].y = point.y + sinf(wallRot[i]) * (TILE_SIZE - LANE_WIDTH / 2);
                }
            }
            else if ((tile.from == SRight && tile.to == SUp) || (tile.from == SUp && tile.to == SRight)) {
                point.x = tileWorldPos.x + TILE_SIZE / 2.f;
                point.y = tileWorldPos.y + TILE_SIZE / 2.f;

                for (unsigned i = 0; i < NUM_WALLS; i++) {
                    wallRot[i] += PI;
                    wallPos[i].x = point.x + cosf(wallRot[i]) * (TILE_SIZE - LANE_WIDTH / 2);
                    wallPos[i].y = point.y + sinf(wallRot[i]) * (TILE_SIZE - LANE_WIDTH / 2);
                }
            }

            Object *wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
            Object_setPos(wall, point);
            CollisionHandler_Create_Circle_Collider(wall, LANE_WIDTH, 0, NULL);
            ObjectManager_addObj(wall);
            
            for (unsigned i = 0; i < NUM_WALLS; i++) {
                wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                Object_setPos(wall, wallPos[i]);
                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { LANE_WIDTH / 2, (TILE_SIZE - LANE_WIDTH / 2) / 2 * PI / NUM_WALLS }, wallRot[i], NULL);
                ObjectManager_addObj(wall);
            }
        }

        if (tile.to == SLeft) tileX--;
        else if (tile.to == SRight) tileX++;
        else if (tile.to == SDown) tileY++;
        else tileY--;
    } while (tileX != initialTileX || tileY != initialTileY);
}
