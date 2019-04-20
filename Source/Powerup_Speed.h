/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Powerup_Speed.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Pedastal powerup
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"


 /**
  * @brief Create new pedstal
  * @param pos Position to create Powerup_Speed at
  * @return New Powerup_Speed
  */
Object *Powerup_Speed_new(AEVec2 pos, Object *parent);
