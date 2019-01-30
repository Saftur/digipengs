/**
 * @file Player.h
 * @author Connor Meyers
 * @date 2019/01/30
 * @brief Object Header for the Player 
 */
#pragma once

#include <AEEngine.h>
#include "Object.h"

 /**
  * @brief Initializes boulder data
  */
void Player_intialize();

/**
 * @brief Frees all allocated memory and calls any ending functions
 */
void Player_shutdown();

/**
 * @brief Create new boulder
 * @param type Type of boulder to create
 * @param pos Position to create boulder at
 * @return New boulder
 */
Object * Player_new();
