/**
 * @file AudioHandler.h
 * @author Richard Folorunso
 * @date 2019/01/09
 * @brief Handles audio output during gameplay.
 */
// Copyright © 2019 DigiPen (USA) Corporation.

#pragma once

void Audio_init();
void Audio_cleanup();

void Audio_playGameplay();
void Audio_stopGameplay();

void Audio_playSfxHitWall();

void Audio_playSfxPolarGrowl();
void Audio_playSfxReady();
void Audio_playSfxSet();
void Audio_playSfxGo();