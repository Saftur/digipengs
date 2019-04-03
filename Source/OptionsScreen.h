#pragma once

/**
 * @file OptionsScreen.h
 * @author Parker Friedland
 * @date 4/3/2019
 * @brief Options Screen
 */

#pragma once
 /**
  * @brief Load Options Screen.
  */
void OptionsScreen_onLoad();

/**
 * @brief Initialize Options Screen.
 */
void OptionsScreen_onInit();

/**
 * @brief Update Options Screen.
 * @param dt Delta Time for updates.
 */
void OptionsScreen_onUpdate(float dt);

/**
 * @brief Shutdown Options Screen.
 */
void OptionsScreen_onShutdown();

/**
 * @brief Unload Options Screen.
 */
void OptionsScreen_onUnload();
