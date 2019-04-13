/**
 * @file Level2.h
 * @author Richard Folorunso
 * @date 1/30/2019
 * @brief Main Level
 */

#pragma once

#define NUM_LAPS 3

#define SHRINK_RATE 0.95f
#define GROW_RATE 1.05f

extern int splitScreen;
extern int keysEnabled;

/**
 * @brief Load Level.
 */
void Level2_onLoad();

/**
 * @brief Initialize Level.
 */
void Level2_onInit();

/**
 * @brief Update Level.
 * @param dt Delta Time for updates.
 */
void Level2_onUpdate(float dt);

/**
 * @brief Draw Level.
 */
void Level2_onDraw();

/**
 * @brief Shutdown Level.
 */
void Level2_onShutdown();

/**
 * @brief Unload Level.
 */
void Level2_onUnload();
