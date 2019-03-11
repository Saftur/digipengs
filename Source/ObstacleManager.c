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

    //Build walls on the map.
    AEVec2 tileWorldPos;
    unsigned tileX = 0, tileY = 0;

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

                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { TILE_SIZE, LANE_WIDTH }, NULL);
                ObjectManager_addObj(wall);

                wallPos.y = tileWorldPos.y - (LANE_WIDTH * 3);
                wallPos.x = tileWorldPos.x;

                wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                Object_setPos(wall, wallPos);

                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { TILE_SIZE, LANE_WIDTH }, NULL);
                ObjectManager_addObj(wall);
            }
            else {
                wallPos.x = tileWorldPos.x + (LANE_WIDTH * 3);
                wallPos.y = tileWorldPos.y;

                Object *wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                Object_setPos(wall, wallPos);

                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { LANE_WIDTH, TILE_SIZE }, NULL);
                ObjectManager_addObj(wall);

                wallPos.x = tileWorldPos.x - (LANE_WIDTH * 3);
                wallPos.y = tileWorldPos.y;

                wall = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                Object_setPos(wall, wallPos);

                CollisionHandler_Create_Square_Collider(wall, (AEVec2) { LANE_WIDTH, TILE_SIZE }, NULL);
                ObjectManager_addObj(wall);
            }
        }
        //Corner tile.
        else {
            AEVec2 wall1Pos;
            AEVec2 wall2Pos;
            AEVec2 wall3Pos;
            AEVec2 wall4Pos;
            switch (tile.from) {
            case SDown:
                switch (tile.to) {
                case SLeft:
                    wall1Pos.x = tileWorldPos.x + (LANE_WIDTH * 3);
                    wall1Pos.y = tileWorldPos.y;
                    wall2Pos.x = tileWorldPos.x + (LANE_WIDTH * 3);
                    wall2Pos.y = tileWorldPos.y;
                    wall3Pos.x = tileWorldPos.x + (LANE_WIDTH * 3);
                    wall3Pos.y = tileWorldPos.y;
                    wall4Pos.x = tileWorldPos.x + (LANE_WIDTH * 3);
                    wall4Pos.y = tileWorldPos.y;

                    Object *wall1 = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                    Object *wall2 = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                    Object *wall3 = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                    Object *wall4 = Object_new(NULL, NULL, NULL, NULL, NULL, "Wall");
                    Object_setPos(wall1, wall1Pos);
                    Object_setPos(wall2, wall2Pos);
                    Object_setPos(wall3, wall3Pos);
                    Object_setPos(wall4, wall4Pos);

                    CollisionHandler_Create_Square_Collider(wall1, (AEVec2) { LANE_WIDTH, LANE_WIDTH }, NULL);
                    CollisionHandler_Create_Square_Collider(wall2, (AEVec2) { LANE_WIDTH, LANE_WIDTH }, NULL);
                    CollisionHandler_Create_Square_Collider(wall3, (AEVec2) { LANE_WIDTH, LANE_WIDTH }, NULL);
                    CollisionHandler_Create_Square_Collider(wall4, (AEVec2) { LANE_WIDTH, LANE_WIDTH }, NULL);
                    ObjectManager_addObj(wall1);
                    ObjectManager_addObj(wall2);
                    ObjectManager_addObj(wall3);
                    ObjectManager_addObj(wall4);
                    break;
                case SRight:
                    break;
                }
                break;
            case SLeft:
                switch (tile.to) {
                case SUp:
                    break;
                case SDown:
                    break;
                }
                break;
            case SRight:
                switch (tile.to) {
                case SUp:
                    break;
                case SDown:
                    break;
                }
                break;
            case SUp:
                switch (tile.to) {
                case SLeft:
                    break;
                case SRight:
                    break;
                }
                break;
            }
        }

        if (tile.to == SLeft) tileX--;
        else if (tile.to == SRight) tileX++;
        else if (tile.to == SDown) tileY++;
        else tileY--;
    } while (tileX != initialTileX || tileY != initialTileY);
}
