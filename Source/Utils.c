/**
 * @file Utils.c
 * @author Arthur Bouvier
 * @date 2/20/2019
 * @brief Utilities implementation
 */
#include "stdafx.h"

#include "Utils.h"
#include <AEEngine.h>

static float dt = 0.067f;

float lerpf(float val1, float val2, float percent) {
    return val1 + (val2 - val1) * percent;
}

float rad_lerpf(float val1, float val2, float percent)
{
    return AEDegToRad(deg_lerpf(AERadToDeg(val1), AERadToDeg(val2), percent));
}

float deg_lerpf(float val1, float val2, float percent) {
    return lerpf((val2 - val1 > 180) ? (val1 + 360) : ((val1 - val2 > 180) ? (val1 - 360) : val1), val2, percent);
}

int randrange(int r1, int r2) {
    return rand() % (r2 - r1 + 1) + r1;
}

float randrangef(float r1, float r2) {
    return ((float)rand() / RAND_MAX) * (r2 - r1) + r1;
}

int randrange_exc(int r1, int r2) {
    return rand() % (r2 - r1) + r1;
}

float randrangef_exc(float r1, float r2) {
    return ((float)rand() / (RAND_MAX+1)) * (r2 - r1) + r1;
}

AEVec2 AEGfxGetWinSize() {
    AEVec2 size;
    size.x = AEGfxGetWinSizeX();
    size.y = AEGfxGetWinSizeY();
    return size;
}

float AEGfxGetWinSizeX() {
    return AEGfxGetWinMaxX() - AEGfxGetWinMinX();
}

float AEGfxGetWinSizeY() {
    return AEGfxGetWinMaxY() - AEGfxGetWinMinY();
}

void AEVec2Rotate(AEVec2 *pResult, AEVec2 *pVec0, f32 rot) {
    AEVec2 tmpResult;
    tmpResult.x = cosf(rot) * pVec0->x - sinf(rot) * pVec0->y;
    tmpResult.y = sinf(rot) * pVec0->x + cosf(rot) * pVec0->y;
    *pResult = tmpResult;
}

void setDt(float deltaTime)
{
	dt = deltaTime;
}

float getDt()
{
	return dt;
}
