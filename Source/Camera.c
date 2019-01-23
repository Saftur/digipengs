/**
 * @file Camera.c
 * @author Arthur Bouvier
 * @brief Camera implementation
 */
#include "stdafx.h"
#include "Camera.h"
#include "vector.h"

typedef struct Camera {
	AEVec2 worldPos;
	float worldRot;
	AEVec2 worldScale;
	AEVec2 viewportPos;
	AEVec2 viewportScale;
} Camera;

static vector *cams;

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

void Camera_new(AEVec2 worldPos, AEVec2 worldScale, float worldRot, AEVec2 viewportPos, AEVec2 viewportScale) {
	Camera *cam = malloc(sizeof(Camera));
	cam->worldPos = worldPos;
	cam->worldScale = worldScale;
	cam->worldRot = worldRot;
	cam->viewportPos = viewportPos;
	cam->viewportScale = viewportScale;
	vector_push_back(cams, cam);
}

void Camera_set(unsigned camNum) {
	if (camNum >= Camera_count())
		return;
	Camera *cam = vector_at(cams, camNum);
	AEGfxSetFullTransform(cam->worldPos.x, cam->worldPos.y, cam->worldRot, cam->worldScale.x, cam->worldScale.y);
	AEGfxSetViewportPositionAndDimensions((int)cam->viewportPos.x, (int)cam->viewportPos.y, (int)cam->viewportScale.x, (int)cam->viewportScale.y);
}
