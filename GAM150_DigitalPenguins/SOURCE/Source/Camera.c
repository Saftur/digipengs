/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Camera.c
 * @author Arthur Bouvier
 * @brief Camera implementation
 */
#include "stdafx.h"
#include "Camera.h"
#include "vector.h"
#include "Utils.h"

static vector *cams;
static Camera *currCam;
static unsigned currCamNum;

void Camera_init() {
	cams = vector_new(2, NULL, free);
}

void Camera_shutdown() {
	vector_delete(cams);
}

void Camera_clear() {
	vector_clear(cams);
}

unsigned Camera_count() {
	return vector_size(cams);
}

Camera *Camera_new(AEVec2 worldPos, float worldScale, float worldRot, AEVec2 viewportPos, AEVec2 viewportSize) {
	Camera *cam = malloc(sizeof(Camera));
    cam->camNum = vector_size(cams);
	cam->worldPos = worldPos;
	cam->worldScale = worldScale;
	cam->worldRot = worldRot;
	cam->viewportPos = viewportPos;
	cam->viewportSize = viewportSize;
	vector_push_back(cams, cam);
    return cam;
}

void Camera_set(unsigned camNum) {
	if (camNum >= Camera_count())
		return;
	currCam = vector_at(cams, camNum);
    currCamNum = camNum;
	AEGfxSetViewportPositionAndDimensions((int)currCam->viewportPos.x, (int)currCam->viewportPos.y, (int)currCam->viewportSize.x, (int)currCam->viewportSize.y);
}

unsigned Camera_getCurrNum() {
    return currCamNum;
}

Camera *Camera_getCurr() {
    return currCam;
}

Camera *Camera_get(unsigned camNum) {
    return vector_at(cams, camNum);
}

void Camera_ScreenCoordToCamCoord(float screenX, float screenY, float *x, float *y, unsigned camNum) {
	Camera *cam = Camera_get(camNum);

	screenX -= cam->viewportPos.x;
	screenY -= cam->viewportPos.y;
	screenX *= AEGfxGetWinSizeX() / cam->viewportSize.x;
	screenY *= AEGfxGetWinSizeY() / cam->viewportSize.y;

	AEGfxConvertScreenCoordinatesToWorld(screenX, screenY, x, y);
}


float Camera_xPos() {
    return currCam->worldPos.x;
}

float Camera_yPos() {
    return currCam->worldPos.y;
}

float Camera_scl() {
    return currCam->worldScale;
}

float Camera_rot() {
    return currCam->worldRot;
}

AEVec2 Camera_apply(Camera * cam, AEVec2 pos)
{
    float rotRad = AEDegToRad(cam->worldRot);
    AEVec2Sub(&pos, &pos, &cam->worldPos);
    AEVec2 newPos;
    newPos.x = cosf(rotRad) * pos.x - sinf(rotRad) * pos.y;
    newPos.y = sinf(rotRad) * pos.x + cosf(rotRad) * pos.y;
    AEVec2Scale(&newPos, &newPos, cam->worldScale);

    return newPos;
}

AEVec2 Camera_applyInverse(Camera * cam, AEVec2 pos) {
    float rotRad = -AEDegToRad(cam->worldRot);
    AEVec2Scale(&pos, &pos, 1.f / cam->worldScale);
    AEVec2 newPos;
    newPos.x = cosf(rotRad) * pos.x - sinf(rotRad) * pos.y;
    newPos.y = sinf(rotRad) * pos.x + cosf(rotRad) * pos.y;
    AEVec2Add(&newPos, &newPos, &cam->worldPos);

    return newPos;
}
