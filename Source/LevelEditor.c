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

static int PlacementMode = 0;
static int ObstacleScale = 32;

static Tile Map[MAP_MAX_SIZE][MAP_MAX_SIZE];
static unsigned Width, Height;
static unsigned TileX, TileY;

static vector *Obstacles;

typedef enum ObstacleType {
    None,
    Boulder
} ObstacleType;

typedef struct {
    ObstacleType type;
    float radius;
    AEVec2 pos;
    void *(*clickEffect)();
} Obstacle;

static void DrawIcons();
static void DrawObstacles();
static void EditMap();
static void LoadMap(const char *filename);
static void SaveMap();
static void ClearMap();

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
}


void LevelEditor_update(float dt)
{
    UNREFERENCED_PARAMETER(dt);

    ///TODO: Remove/change this key.
    if (AEInputCheckTriggered('L')) LevelManager_setNextLevel(Level2);

    DrawIcons();
    if (Camera_getCurr()) DrawObstacles();

    if (Camera_getCurr()) Map_customDraw(Map, Height, Width);

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

    /*if (Camera_getCurr()) AEVec2Sub(&placementLoc, &mouseLoc, &Camera_getCurr()->worldPos);


    placementLoc.x = cosf(0) * mouseLoc.x - sinf(0) * mouseLoc.y;
    placementLoc.y = sinf(0) * mouseLoc.x + cosf(0) * mouseLoc.y;

    if (Camera_getCurr()) AEVec2Scale(&placementLoc, &placementLoc, Camera_scl());
    if (Camera_getCurr()) AEVec2Add(&placementLoc, &placementLoc, &Camera_getCurr()->worldPos);*/

    if (AEInputCheckCurr(VK_ADD)) ObstacleScale++;
    if (AEInputCheckCurr(VK_SUBTRACT)) ObstacleScale--;

    switch (PlacementMode) {
    //Boulder
    case 1:
        ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.boulder, mouseLoc, (float)ObstacleScale, 0, 1);

        if (AEInputCheckTriggered(VK_LBUTTON)) {
            Obstacle *boulder = malloc(sizeof(Obstacle));
            boulder->type = Boulder;
            boulder->radius = ObstacleScale / 2.f;
            boulder->pos = placementLoc;
            boulder->clickEffect = NULL;

            vector_push_back(Obstacles, boulder);
        }
        break;

    case 0:
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
    for (int y = 0; y < MAP_MAX_SIZE; y++) {
        for (int x = 0; x < MAP_MAX_SIZE; x++) {
            Map[y][x] = (Tile) { SNone, SNone, TTNone };
        }
    }
    Width = 1;
    Height = 1;
    TileX = 0;
    TileY = 0;

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
}

static void ClearMap() {
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

    ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.boulder, iconPos, 32, 0, 1);

    AEVec2Add(&iconPos, &iconPos, &distBetweenIcons);
}

void DrawObstacles()
{
    for (unsigned i = 0; i < vector_size(Obstacles); i++) {
        Obstacle obstacle = *(Obstacle*) vector_at(Obstacles, i);

        switch (obstacle.type) {
        case Boulder:
            ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), TEXTURES.boulder, obstacle.pos, obstacle.radius * 2, 0, 1);
            break;
        }
    }
}
