/**
 * @file MeshHandler.h
 * @author Connor Meyers
 * @date 2019/01/10
 * @brief Creates meshes given a size
 */

#pragma once

#include "AEEngine.h"
 /**
  * @brief Returns a pre-created mesh or creates it (the first time)
  * @return A pointer to a mesh
  */
AEGfxVertexList *MeshHandler_getSquareMesh();

/**
 * @brief creates a mesh
 * @param xHalfSize Half width of the mesh
 * @param yHalfSize Half height of the mesh
 * @param uSize U value for spritesheet
 * @param vSize V value for spritesheet
 * @return A pointer to a mesh
 */
AEGfxVertexList* MeshHandler_createSquareMesh (float xHalfSize, float yHalfSize, float uSize, float vSize);