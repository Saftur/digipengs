/**
 * @file Level1.h
 * @author Brand Knutson
 * @date 1/10/2019
 * @brief First Level
 */

#pragma once
 /**
  * @brief Load TitleScreen.
  */
void TitleScreen_onLoad();

/**
 * @brief Initialize TitleScreen.
 */
void TitleScreen_onInit();

/**
 * @brief Update TitleScreen.
 * @param dt Delta Time for updates.
 */
void TitleScreen_onUpdate(float dt);

/**
 * @brief Shutdown TitleScreen.
 */
void TitleScreen_onShutdown();

/**
 * @brief Unload TitleScreen.
 */
void TitleScreen_onUnload();
