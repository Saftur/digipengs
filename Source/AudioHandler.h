/**
 * @file AudioHandler.h
 * @author Richard Folorunso
 * @date 2019/01/09
 * @brief Handles audio output during gameplay.
 */
// Copyright © 2019 DigiPen (USA) Corporation.

#pragma once

#define MIN_VOLUME 0.0f
#define MAX_VOLUME 1.0f

extern float musicVolume;
extern float SFXVolume;

void Audio_init();
void AudioUpdate();
void Audio_cleanup();

void Audio_playGameplay();
void Audio_stopGameplay();

void Audio_playSfxHitWall();

void Audio_playSfxPolarGrowl();
void Audio_playSfxReady();
void Audio_playSfxSet();
void Audio_playSfxGo();