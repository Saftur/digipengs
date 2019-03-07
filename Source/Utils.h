/**
 * @file Utils.h
 * @author Arthur Bouvier
 * @date 2/20/2019
 * @brief Utilities
 */
#pragma once

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
