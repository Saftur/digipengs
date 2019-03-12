/**
 * @file Camera.h
 * @author Arthur Bouvier
 * @brief Camera interface
 */
#pragma once

#include <AEEngine.h>

typedef struct Camera {
	AEVec2 worldPos;
	float worldRot;
	float worldScale;
	AEVec2 viewportPos;
	AEVec2 viewportSize;
} Camera;

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

/**
 * @brief Get current number of Cameras
 * @return Number of Cameras
 */
unsigned Camera_count();

/**
 * @brief Create new Camera
 * @param worldPos     Position in the world
 * @param worldScale   Scale of the world
 * @param worldRot     Rotation of the world
 * @param viewportPos  Position in window
 * @param viewportSize Size in window
 */
void Camera_new(AEVec2 worldPos, float worldScale, float worldRot, AEVec2 viewportPos, AEVec2 viewportSize);

/**
 * @brief Set current Camera
 * @param camNum Camera number
 */
void Camera_set(unsigned camNum);

unsigned Camera_getCurrNum();

Camera *Camera_getCurr();

Camera *Camera_get(unsigned camNum);

/**
 * @brief Get current Camera X pos
 * @return Camera X pos
 */
float Camera_xPos();

/**
 * @brief Get current Camera Y pos
 * @return Camera Y pos
 */
float Camera_yPos();

/**
 * @brief Get current Camera scale
 * @return Camera scale
 */
float Camera_scl();

/**
 * @brief Get current Camera rotation
 * @return Camera rotation
 */
float Camera_rot();

/**
 * @brief Converts world position to screen position related to given camera.
 *
 * @param cam Camera to ascertain transform from
 *
 * @param pos Position to use for calculations
 *
 * @return New position
 */
AEVec2 Camera_apply(Camera * cam, AEVec2 pos);

/**
 * @brief Turns screen position into world position related to given camera.
 *
 * @param cam Camera to ascertain transform from
 *
 * @param pos Position to use for calculations
 *
 * @return New position
 */
AEVec2 Camera_applyInverse(Camera * cam, AEVec2 pos);
