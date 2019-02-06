/**
 * @file Camera.c
 * @author Arthur Bouvier
 * @brief Camera implementation
 */
#include "stdafx.h"
#include "Camera.h"
#include "vector.h"

/*typedef struct Camera {
	AEVec2 worldPos;
	float worldRot;
	AEVec2 worldScale;
	AEVec2 viewportPos;
	AEVec2 viewportSize;
} Camera;*/

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

void Camera_new(AEVec2 worldPos, AEVec2 worldScale, float worldRot, AEVec2 viewportPos, AEVec2 viewportSize) {
	Camera *cam = malloc(sizeof(Camera));
	cam->worldPos = worldPos;
	cam->worldScale = worldScale;
	cam->worldRot = worldRot;
	cam->viewportPos = viewportPos;
	cam->viewportSize = viewportSize;
	vector_push_back(cams, cam);
}

void Camera_set(unsigned camNum) {
	if (camNum >= Camera_count())
		return;
	currCam = vector_at(cams, camNum);
    currCamNum = camNum;
	AEGfxSetViewportPositionAndDimensions((int)currCam->viewportPos.x, (int)currCam->viewportPos.y, (int)currCam->viewportSize.x, (int)currCam->viewportSize.y);
    //AEGfxSetCamPosition(currCam->worldPos.x, currCam->worldPos.y);
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

float Camera_xPos() {
    return currCam->worldPos.x;
}

float Camera_yPos() {
    return currCam->worldPos.y;
}

float Camera_xScl() {
    return currCam->worldScale.x;
}

float Camera_yScl() {
    return currCam->worldScale.y;
}

float Camera_rot() {
    return currCam->worldRot;
}
