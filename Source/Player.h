/**
 * @file Player.h
 * @author Connor Meyers
 * @date 2019/01/30
 * @brief Object * Header for the Player 
 */
#pragma once
#include <AEEngine.h>
#include "Object.h"

#define PLAYER_STANDARD_TEXTURE TEXTURES.player
#define PLAYER_SCALE (AEVec2){30,36}

/**
 * @brief Frees all allocated memory and calls any ending functions
 */
void Player_shutdown();

/**
 * @brief Create new Player
 * @param pos Position to create player at
 * @return New player
 */
Object * Player_new(AEVec2 pos);

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
void Player_changeTexture(Object * player, AEGfxTexture * texture);

/**
 * @brief Returns the alpha of a player
 * @param player Player to get the alpha of
 * @return Alpha from 0 to 1
 */
float Player_getAlpha(Object * player);

/**
 * @brief Sets the alpha of a player
 * @param player Player to set the alpha of
 * @param alpha New alpha (clamped between 0 and 1)
 */
void Player_setAlpha(Object * player, float alpha);