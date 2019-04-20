/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Powerup_Blind.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Powerup_Blind powerup
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"


 /**
  * @brief Create new pedstal
  * @param pos Position to create Powerup_Blind at
  * @return New Powerup_Blind
  */
Object *Powerup_Blind_new(AEVec2 pos, Object *parent);
