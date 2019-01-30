/**
 * @file Player.h
 * @author Connor Meyers
 * @date 2019/01/30
 * @brief Object * Header for the Player 
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
Object *Player_new();

/**
 * @brief Returns the transform of a player
 * @param player Player to get the transform of
 * @return Transform
 */
AEVec2 Player_getTransform(Object * player);

/**
 * @brief Sets the transform of a player
 * @param player Player to set the transform of
 * @param vec New Transform
 */
void Player_setTransform(Object * player, AEVec2 vec);

/**
 * @brief Returns the direction of a player
 * @param player Player to get the direction of
 * @return Direction from -1 to 1
 */
float Player_getDirection(Object * player);

/**
 * @brief Sets the direction of a player
 * @param player Player to set the direction of
 * @param dir New direction (clamped between -1 and 1)
 */
void Player_setDirection(Object * player, float dir);

/**
 * @brief Changes the texture of a player
 * @param player Player to set the texture of
 * @param texture New Texture
 */
void Player_changeTexture(Object * player, AEGfxTexture texture);
