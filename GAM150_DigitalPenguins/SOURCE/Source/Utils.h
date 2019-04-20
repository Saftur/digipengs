/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Utils.h
 * @author Arthur Bouvier
 * @date 2/20/2019
 * @brief Utilities
 */
#pragma once

#include <AEVec2.h>
#include <Windows.h>

/**
 * @brief Lerp float values
 * @param val1    Value to start at
 * @param val2    Value to go to
 * @param percent Percent of the way to go to val2
 * @return Result
 */
float lerpf(float val1, float val2, float percent);


/**
 * @brief Lerp float angle
 * Will go the shortest way
 * @param val1    Angle to start at
 * @param val2    Angle to go to
 * @param percent Percent of the way to go to val2
 * @return Result
 */
float rad_lerpf(float val1, float val2, float percent);

/**
 * @brief Lerp float angle
 * Will go the shortest way
 * @param val1    Angle to start at
 * @param val2    Angle to go to
 * @param percent Percent of the way to go to val2
 * @return Result
 */
float deg_lerpf(float val1, float val2, float percent);

/**
 * @brief Generate a random integer in given range (inclusive) 
 * @param r1 Left bound
 * @param r2 Right bound
 */
int randrange(int r1, int r2);
/**
 * @brief Generate a random float in given range (inclusive) 
 * @param r1 Left bound
 * @param r2 Right bound
 */
float randrangef(float r1, float r2);

/**
 * @brief Generate a random integer in given range (exclusive) 
 * @param r1 Left bound
 * @param r2 Right bound
 */
int randrange_exc(int r1, int r2);
/**
 * @brief Generate a random float in given range (exclusive) 
 * @param r1 Left bound
 * @param r2 Right bound
 */
float randrangef_exc(float r1, float r2);

AEVec2 AEGfxGetWinSize();

float AEGfxGetWinSizeX();
float AEGfxGetWinSizeY();

/**
 * @brief Rotate AEVec2 by given angle
 * @param[out] pResult Where to store result
 * @param pVec0        AEVec2 to rotate
 * @param rot          Angle to rotate by in radians
 */
void AEVec2Rotate(AEVec2 *pResult, AEVec2 *pVec0, f32 rot);

/*
 * @brief Set the game's dt value;
 * @param deltaTime The value to set dt to.
*/
void setDt(float deltaTime);

/*
 * @brief Get the game's dt value;
 * @return Current game delta time.
*/
float getDt();

FILE *openAppdataFile(const char *filename, const char *mode);

BOOL copyAssetToAppdata(const char *filename, const char *newFilename);
