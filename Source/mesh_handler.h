/**
 * @file mesh_handler.h
 * @author Connor Meyers
 * @date 2019/01/10
 * @brief Creates meshes given a size
 */

#pragma once

#include "AEEngine.h"

/**
 * @brief
 * @param width Width of the mesh
 * @param height Height of the mesh
 * @return A pointer to a mesh
 * @par Example: 
 * @code 
 * AEGfxVertexList *squareMesh = createSquareMesh(200, 200); 
 * @endcode
 */
AEGfxVertexList* createSquareMesh(float width, float height);