/**
 * @file Camera.h
 * @author Arthur Bouvier
 * @brief Camera interface
 */
#pragma once

#include <AEEngine.h>

/**
 * @brief Initialize Cameras
 */
void Camera_init();

/**
 * @brief Shutdown Cameras
 */
void Camera_shutdown();

/**
 * @brief Delete all Cameras
 */
void Camera_clear();

unsigned Camera_count();

void Camera_new(AEVec2 worldPos, AEVec2 worldScale, float worldRot, AEVec2 viewportPos, AEVec2 viewportScale);

void Camera_set(unsigned camNum);
