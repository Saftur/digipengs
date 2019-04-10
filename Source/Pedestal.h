/**
 * @file Pedestal.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Pedastal powerup
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"

/**
 * @brief Create new pedstal
 * @param pos Position to create pedestal at
 * @return New pedestal
 */
Object *Pedestal_new(AEVec2 pos);

void Pedestal_resetPowerup(Object *pedestal);