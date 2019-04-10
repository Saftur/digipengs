/**
 * @file BlindObject.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the BlindObject powerup
 */

#pragma once

#include <AEEngine.h>
#include "Object.h"


 /**
  * @brief Create new pedstal
  * @param pos Position to create BlindObject at
  * @return New BlindObject
  */
Object *BlindObject_new(unsigned camNum);
