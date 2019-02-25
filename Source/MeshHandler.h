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
 * @param width Width of the mesh
 * @param height Height of the mesh
 * @return A pointer to a mesh
 * @par Example: 
 * @code 
 * AEGfxVertexList *squareMesh = MeshHandler_createSquareMesh(200, 200); 
 * @endcode
 */
AEGfxVertexList* MeshHandler_createSquareMesh(float width, float height);