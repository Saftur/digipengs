/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
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
        SquareMesh = MeshHandler_createSquareMesh(0.5, 0.5, 1, 1);

    return SquareMesh;
}

AEGfxVertexList* MeshHandler_createSquareMesh(float xHalfSize, float yHalfSize, float uSize, float vSize)
{
	AEGfxVertexList* squareMesh;

	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-xHalfSize, -yHalfSize, 0x00FF00FF, 0.0f, vSize,
		xHalfSize, -yHalfSize, 0x00FFFF00, uSize, vSize,
		-xHalfSize, yHalfSize, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		xHalfSize, -yHalfSize, 0x00FFFFFF, uSize, vSize,
		xHalfSize, yHalfSize, 0x00FFFFFF, uSize, 0.0f,
		-xHalfSize, yHalfSize, 0x00FFFFFF, 0.0f, 0.0f);

    squareMesh = AEGfxMeshEnd();

    AE_ASSERT_MESG(squareMesh, "Failed to create mesh");

    return squareMesh;
}