/**
 * @file EndScreen.h
 * @author Parker Friedland
 * @date 3/10/2019
 * @brief End screen
 */
#pragma once

extern int EndScreen_winner;

 /**
  * @brief Load TitleScreen.
  */
void EndScreen_onLoad();

/**
 * @brief Initialize TitleScreen.
 */
void EndScreen_onInit();

/**
 * @brief Update TitleScreen.
 * @param dt Delta Time for updates.
 */
void EndScreen_onUpdate(float dt);

/**
 * @brief Draw TitleScreen.
 */
void EndScreen_onDraw();

/**
 * @brief Shutdown TitleScreen.
 */
void EndScreen_onShutdown();

/**
 * @brief Unload TitleScreen.
 */
void EndScreen_onUnload();
