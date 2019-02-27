/**
 * @file Utils.c
 * @author Arthur Bouvier
 * @date 2/20/2019
 * @brief Utilities implementation
 */
#include "stdafx.h"

#include "Utils.h"

float lerpf(float val1, float val2, float percent) {
    return val1 + (val2 - val1) * percent;
}

float deg_lerpf(float val1, float val2, float percent) {
    return lerpf((val2 - val1 > 180) ? (val1 + 360) : ((val1 - val2 > 180) ? (val1 - 360) : val1), val2, percent);
}
