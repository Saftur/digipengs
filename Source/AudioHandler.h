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