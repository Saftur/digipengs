/**
 * @file LevelEditor.c
 * @author Brand Knutson
 * @date 2/20/2019
 * @brief Manage and create levels with a GUI.
 */

#include "stdafx.h"
#include "objectmanager.h"
#include "object.h"
#include "vector.h"
#include "LevelEditor.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Map.h"
#include "Camera.h"
#include "LevelManager.h"
#include "ObstacleManager.h"

#define BOULDER_TEXTURE TEXTURES.boulder
#define POLARBEAR_TEXTURE TEXTURES.test
#define ICE_TEXTURE TEXTURES.test

static int PlacementMode = 0;
static int ObstacleScale = 32;

static Tile Map[MAP_MAX_SIZE][MAP_MAX_SIZE];
static unsigned Width, Height;
static unsigned TileX, TileY;

static vector *Obstacles;

static void DrawIcons();
static void DrawObstacles();
static void EditMap();
static void LoadMap(const char *filename);
static void SaveMap();
static void ClearMap();
static void LoadObstacles();

void LevelEditor_init()
{
    for (int y = 0; y < MAP_MAX_SIZE; y++) {
        for (int x = 0; x < MAP_MAX_SIZE; x++) {
            Map[y][x] = (Tile) { SNone, SNone, TTNone };
        }
    }
    Map[0][0] = (Tile) { SDown, SRight, TTTurn };

    Width = 1;
    Height = 1;
    TileX = 0;
    TileY = 0;

    Obstacles = vector_new(5, NULL, free);

    LoadMap("./Assets/Map.txt");
    LoadObstacles();
}


void LevelEditor_update(float dt)
{
    UNREFERENCED_PARAMETER(dt);

    if (Camera_getCurr()) Map_customDraw(Map, Height, Width);
    DrawIcons();
    if (Camera_getCurr()) DrawObstacles();

    for (u8 i = '0'; i < '9'; i++) {
        if (AEInputCheckTriggered(i)) PlacementMode = i - '0';
    }

    s32 screenX, screenY;
    AEInputGetCursorPosition(&screenX, &screenY);

    //Convert mouse screen position to world position.
    float mouseX;
    float mouseY;
    AEGfxConvertScreenCoordinatesToWorld((float)screenX, (float)screenY, &mouseX, &mouseY);

    AEVec2 mouseLoc;
    mouseLoc.x = mouseX;
    mouseLoc.y = mouseY;

    AEVec2 placementLoc = mouseLoc;
    if (Camera_getCurr()) placementLoc = Camera_applyInverse(Camera_getCurr(), mouseLoc);

    if (AEInputCheckCurr(VK_RSHIFT)) ObstacleScale++;
    if (AEInputCheckCurr(VK_LSHIFT)) ObstacleScale--;

    //Remove obstacles when they are clicked.
    if (AEInputCheckTriggered(VK_LBUTTON)) {
        for (unsigned i = 0; i < vector_size(Obstacles); i++) {
            Obstacle *obstacle = vector_at(Obstacles, i);

            float distance = AEVec2Distance(&placementLoc, &(obstacle->pos));
            if (distance < obstacle->radius) {
                PlacementMode = obstacle->type;
                ObstacleScale = (int)obstacle->radius * 2;
                vector_erase(Obstacles, i);
                return;
            }
        }
    }

    switch (PlacementMode) {
    case Boulder:
        ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), BOULDER_TEXTURE, mouseLoc, (float)ObstacleScale * Camera_getCurr()->worldScale, 0, 1);

        if (AEInputCheckTriggered(VK_LBUTTON)) {
            Obstacle *boulder = malloc(sizeof(Obstacle));
            boulder->type = Boulder;
            boulder->radius = ObstacleScale / 2.f;
            boulder->pos = placementLoc;
            boulder->rotation = 0;

            vector_push_back(Obstacles, boulder);
        }
        break;
    case Polarbear:
        ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), POLARBEAR_TEXTURE, mouseLoc, (float)ObstacleScale * Camera_getCurr()->worldScale, 0, 1);

        if (AEInputCheckTriggered(VK_LBUTTON)) {
            Obstacle *polarbear = malloc(sizeof(Obstacle));
            polarbear->type = Polarbear;
            polarbear->radius = ObstacleScale / 2.f;
            polarbear->pos = placementLoc;
            polarbear->rotation = 0;

            vector_push_back(Obstacles, polarbear);
        }
        break;
    case Ice:
        ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), ICE_TEXTURE, mouseLoc, (float)ObstacleScale * Camera_getCurr()->worldScale, 0, 1);

        if (AEInputCheckTriggered(VK_LBUTTON)) {
            Obstacle *ice = malloc(sizeof(Obstacle));
            ice->type = Ice;
            ice->radius = ObstacleScale / 2.f;
            ice->pos = placementLoc;
            ice->rotation = 0;

            vector_push_back(Obstacles, ice);
        }
        break;

    case None:
        EditMap();
        break;
        
    default:
        break;
    }
}

void LevelEditor_shutdown()
{
    vector_delete(Obstacles);
}

static void EditMap() {
    Tile currTile = Map[TileY][TileX];

    //unsigned nextTileX = TileX;
    //unsigned nextTileY = TileY;

    //if (currTile.to == SRight) nextTileX++;
    //if (currTile.to == SLeft) nextTileX--;
    //if (currTile.to == SUp) nextTileY--;
    //if (currTile.to == SDown) nextTileY++;
    
    if (AEInputCheckTriggered(VK_BACK)) {
        Side from = Map[TileY][TileX].from;
        Map[TileY][TileX] = (Tile) { SNone, SNone, TTNone };
        if (from == SLeft) TileX--;
        if (from == SRight) TileX++;
        if (from == SUp) TileY--;
        if (from == SDown) TileY++;
    }

    if (AEInputCheckTriggered('R')) LevelManager_setNextLevel(LevelRestart);

    if (AEInputCheckTriggered(VK_INSERT)) ClearMap();
    if (AEInputCheckTriggered(VK_RETURN)) SaveMap();
    if (AEInputCheckTriggered(VK_DELETE)) {
        LoadMap("./Assets/DefaultMap.txt");
        SaveMap();
    }

    switch (currTile.to) {
    case SUp:
        if (Map[TileY - 1][TileX].type != TTNone) return;
        break;
    case SDown:
        if (Map[TileY + 1][TileX].type != TTNone) return;
        break;
    case SLeft:
        if (Map[TileY][TileX - 1].type != TTNone) return;
        break;
    case SRight:
        if (Map[TileY][TileX + 1].type != TTNone) return;
        break;
    }

    if (AEInputCheckTriggered(VK_UP) && (int)TileY - 1 > 0) {
        switch (currTile.to) {
        case SUp:
            Map[--TileY][TileX] = (Tile) { SDown, SUp, TTVert };
            break;
        case SLeft:
            Map[TileY][--TileX] = (Tile) { SRight, SUp, TTTurn };
            break;
        case SRight:
            Map[TileY][++TileX] = (Tile) { SLeft, SUp, TTTurn };
            if(TileX > Width - 1) Width = TileX + 1;
            break;
        }
    }
    if (AEInputCheckTriggered(VK_DOWN) && TileY + 2 < MAP_MAX_SIZE) {
        switch (currTile.to) {
        case SDown:
            Map[++TileY][TileX] = (Tile) { SUp, SDown, TTVert };
            if (TileY > Height - 1) Height = TileY + 1;
            break;
        case SLeft:
            Map[TileY][--TileX] = (Tile) { SRight, SDown, TTTurn };
            break;
        case SRight:
            Map[TileY][++TileX] = (Tile) { SLeft, SDown, TTTurn };
            if (TileX > Width - 1) Width = TileX + 1;
            break;
        }
    }
    if (AEInputCheckTriggered(VK_LEFT) && (int)TileX - 1 > 0) {
        switch (currTile.to) {
        case SUp:
            Map[--TileY][TileX] = (Tile) { SDown, SLeft, TTTurn };
            break;
        case SLeft:
            Map[TileY][--TileX] = (Tile) { SRight, SLeft, TTVert };
            break;
        case SDown:
            Map[++TileY][TileX] = (Tile) { SUp, SLeft, TTTurn };
            if (TileY > Height - 1) Height = TileY + 1;
            break;
        }
    }
    if (AEInputCheckTriggered(VK_RIGHT) && TileX + 2 < MAP_MAX_SIZE) {
        switch (currTile.to) {
        case SUp:
            Map[--TileY][TileX] = (Tile) { SDown, SRight, TTVert };
            break;
        case SDown:
            Map[++TileY][TileX] = (Tile) { SUp, SRight, TTTurn };
            if (TileY > Height - 1) Height = TileY + 1;
            break;
        case SRight:
            Map[TileY][++TileX] = (Tile) { SLeft, SRight, TTVert };
            if (TileX > Width - 1) Width = TileX + 1;
            break;
        }
    }
}

static void LoadMap(const char *filename) {
    ClearMap();

    FILE *file;
    fopen_s(&file, filename, "rt");
    if (!file)
        return;
    Width = 1;
    int c;
    unsigned x = 0, y = 0;
    int which = 0;
    while ((c = fgetc(file)) != EOF) {
        if (which > 1) {
            Tile *t = &Map[y][x];
            if (t->from == SLeft && t->to == SRight ||
                t->from == SRight && t->to == SLeft)
                t->type = TTHoriz;
            else if (t->from == SUp && t->to == SDown ||
                t->from == SDown && t->to == SUp)
                t->type = TTVert;
            else t->type = TTTurn;
            x++;
            which = 0;
            if (x > Width)
                Width = x;
        }
        switch (c) {
        case 'L':
            if (which)
                Map[y][x].to = SLeft;
            else Map[y][x].from = SLeft;
            which++;
            break;
        case 'R':
            if (which)
                Map[y][x].to = SRight;
            else Map[y][x].from = SRight;
            which++;
            break;
        case 'U':
            if (which)
                Map[y][x].to = SUp;
            else Map[y][x].from = SUp;
            which++;
            break;
        case 'D':
            if (which)
                Map[y][x].to = SDown;
            else Map[y][x].from = SDown;
            which++;
            break;
        case 'N':
            if (which)
                Map[y][x].to = SNone;
            else Map[y][x].from = SNone;
            which++;
            break;
        case '\n':
            if (x > 0) {
                y++;
                x = 0;
                which = 0;
            }
            break;
        }
    }
    fclose(file);
    if (which > 1) {
        Tile *t = &Map[y][x];
        if (t->from == SLeft && t->to == SRight ||
            t->from == SRight && t->to == SLeft)
            t->type = TTHoriz;
        else if (t->from == SUp && t->to == SDown ||
            t->from == SDown && t->to == SUp)
            t->type = TTVert;
        else t->type = TTTurn;
    }
    if (x > 0)
        y++;
    Height = y;
    TileY = y - 1;
    TileX = x;
}

void LoadObstacles() {
    FILE *file;
    fopen_s(&file, "./Assets/ObstacleMap.txt", "rt");
    if (!file) return;

    Obstacle *obstacle;
    char obstacleType;
    while ((obstacleType = (char)fgetc(file)) != EOF) {
        obstacle = malloc(sizeof(Obstacle));
        char locString[6];
        locString[5] = '\0';

        obstacle->radius = (float)atoi(fgets(locString, 6, file));
        obstacle->pos.x = (float)atoi(fgets(locString, 6, file));
        obstacle->pos.y = (float)atoi(fgets(locString, 6, file));
        obstacle->rotation = (float)atoi(fgets(locString, 6, file));

        switch (obstacleType) {
        case 'B':
            obstacle->type = Boulder;
            break;
        case 'P':
            obstacle->type = Polarbear;
            break;
        case 'I':
            obstacle->type = Ice;
            break;
        }

        vector_push_back(Obstacles, obstacle);
    }
    fclose(file);
}

static void SaveMap() {
    FILE *file;
    fopen_s(&file, "./Assets/Map.txt", "w");
    if (!file)
        return;

    for (unsigned y = 0; y < Height; y++) {
        for (unsigned x = 0; x < Width; x++) {
            Side from = Map[y][x].from;
            Side to = Map[y][x].to;

            if (from == SLeft) fputc('L', file);
            else if (from == SRight) fputc('R', file);
            else if (from == SUp) fputc('U', file);
            else if (from == SDown) fputc('D', file);
            else if (from == SNone) fputc('N', file);

            if (to == SLeft) fputc('L', file);
            else if (to == SRight) fputc('R', file);
            else if (to == SUp) fputc('U', file);
            else if (to == SDown) fputc('D', file);
            else if (to == SNone) fputc('N', file);

            fputc(' ', file);
        }
        if (y < Height - 1) fputc('\n', file);
    }

    fclose(file);

    fopen_s(&file, "./Assets/ObstacleMap.txt", "w");

    for (unsigned i = 0; i < vector_size(Obstacles); i++) {
        Obstacle *obstacle = vector_at(Obstacles, i);
        switch (obstacle->type) {
        case Boulder:
            fputc('B', file);
            break;
        case Polarbear:
            fputc('P', file);
            break;
        case Ice:
            fputc('I', file);
            break;
        }

        fprintf(file, "%5d%5d%5d%5d", (int)obstacle->radius, (int)obstacle->pos.x, (int)obstacle->pos.y, (int)obstacle->rotation);
    }
    fclose(file);
}

static void ClearMap() {
    vector_clear(Obstacles);

    for (int y = 0; y < MAP_MAX_SIZE; y++) {
        for (int x = 0; x < MAP_MAX_SIZE; x++) {
            Map[y][x] = (Tile) { SNone, SNone, TTNone };
        }
    }
    Map[0][0] = (Tile) { SDown, SRight, TTTurn };

    Width = 1;
    Height = 1;
    TileX = 0;
    TileY = 0;
}

static void DrawIcons() {
    AEVec2 iconPos;
    AEVec2 distBetweenIcons = { 64, 0 };
    iconPos.x = AEGfxGetWinMinX() + 50;
    iconPos.y = AEGfxGetWinMaxY() - 50;

    ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), BOULDER_TEXTURE, iconPos, 32, 0, 1);
    AEVec2Add(&iconPos, &iconPos, &distBetweenIcons);
    ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), POLARBEAR_TEXTURE, iconPos, 32, 0, 1);
    AEVec2Add(&iconPos, &iconPos, &distBetweenIcons);
    ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), ICE_TEXTURE, iconPos, 32, 0, 1);
    AEVec2Add(&iconPos, &iconPos, &distBetweenIcons);
}

void DrawObstacles()
{
    for (unsigned i = 0; i < vector_size(Obstacles); i++) {
        Obstacle obstacle = *(Obstacle*) vector_at(Obstacles, i);

        switch (obstacle.type) {
        case Boulder:
            ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), BOULDER_TEXTURE, obstacle.pos, obstacle.radius * 2, 0, 1);
            break;
        case Polarbear:
            ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), POLARBEAR_TEXTURE, obstacle.pos, obstacle.radius * 2, 0, 1);
            break;
        case Ice:
            ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), ICE_TEXTURE, obstacle.pos, obstacle.radius * 2, 0, 1);
            break;
        }
    }
}
