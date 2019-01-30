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
void Camera_new(AEVec2 worldPos, AEVec2 worldScale, float worldRot, AEVec2 viewportPos, AEVec2 viewportSize);

/**
 * @brief Set current Camera
 * @param camNum Camera number
 */
void Camera_set(unsigned camNum);

/**
 * @brief Get current Camera X scale
 * @return Camera X scale
 */
float Camera_xScl();

/**
 * @brief Get current Camera Y scale
 * @return Camera Y scale
 */
float Camera_yScl();

/**
 * @brief Get current Camera rotation
 * @return Camera rotation
 */
float Camera_rot();
