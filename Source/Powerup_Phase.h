/**
 * @file Powerup_Phase.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Powerup_Phase powerup
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"

 /**
  * @brief Create new pedstal
  * @param pos Position to create Powerup_Phase at
  * @return New Powerup_Phase
  */
Object *Powerup_Phase_new(AEVec2 pos, Object *parent);
