/**
 * @file MeshHandler.c
 * @author Connor Meyers
 * @date 2019/01/10
 * @brief Creates meshes given a size
 */

#include "stdafx.h"		// Should be included first in every .c file!

#include "MeshHandler.h"

AEGfxVertexList *SquareMesh = NULL;

AEGfxVertexList *MeshHandler_getSquareMesh()
{
    if (!SquareMesh)
        SquareMesh = MeshHandler_createSquareMesh(1, 1);

    return SquareMesh;
}

AEGfxVertexList* MeshHandler_createSquareMesh(float width, float height)
{
    AEGfxVertexList* squareMesh;

	width /= 2;
	height /= 2;

    // Informing the library that we're about to start adding triangles
    AEGfxMeshStart();

    // This shape has 2 triangles
    AEGfxTriAdd(
        -width, -height, 0x00FF00FF, 0.0f, 1.0f,
        width, -height, 0x00FFFF00, 1.0f, 1.0f,
        -width, height, 0x00F00FFF, 0.0f, 0.0f);

    AEGfxTriAdd(
        width, -height, 0x00FFFFFF, 1.0f, 1.0f,
        width, height, 0x00FFFFFF, 1.0f, 0.0f,
        -width, height, 0x00FFFFFF, 0.0f, 0.0f);

    squareMesh = AEGfxMeshEnd();

    AE_ASSERT_MESG(squareMesh, "Failed to create mesh");

    return squareMesh;
}