/**
 * @file AudioHandler.c
 * @author Richard Folorunso
 * @date 2019/01/09
 * @brief Handles audio output during gameplay.
 */
// Copyright © 2019 DigiPen (USA) Corporation.

#include "stdafx.h" // Should be included first in every .c file!

#include "AudioHandler.h"
#include "fmod.h"
#include <stdio.h>		// printf()
#include <stdbool.h>	// FALSE

FMOD_SYSTEM *soundSystem;
FMOD_SYSTEM *sfxSystem;
FMOD_CHANNEL *MusicChannel = 0;
FMOD_CHANNEL *SFXChannel = 0;
FMOD_RESULT result;

// Contains all the music/soundeffects in the game
FMOD_SOUND *bgmGameplay;
FMOD_SOUND *sfxPlayerHitWall;
FMOD_SOUND *sfxPolarGrowl;
FMOD_SOUND *sfxReady;
FMOD_SOUND *sfxSet;
FMOD_SOUND *sfxGo;

//FMOD_Channel_SetMode(MusicChannel, FMOD_LOOP_OFF);
//FMOD_Channel_SetLoopCount(FMOD_CHANNEL *MusicChannel, int loopcount);

// Helper function to check for errors
static void ERRCHECK(const FMOD_RESULT checkResult)
{
	if (checkResult != FMOD_OK)
	{
		printf("There was an error in the audio system");
	}
}

// Initialize the Audio System
void Audio_init()
{
	// Create and Initialize the FMOD System
	result = FMOD_System_Create(&soundSystem);
	ERRCHECK(result);

  result = FMOD_System_Create(&sfxSystem);
  ERRCHECK(result);

	void *extradriverdata = 0;
	result = FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, extradriverdata);
  ERRCHECK(result);

  void *extrasfxdriverdata = 0;
  result = FMOD_System_Init(sfxSystem, 32, FMOD_INIT_NORMAL, extrasfxdriverdata);
  ERRCHECK(result);
}

// Update the Audio System
// Note: this should be called frequently such as every game loop or
//       every time a user enters a command depending on the engine
void AudioUpdate()
{
	result = FMOD_System_Update(soundSystem);
	ERRCHECK(result);
  result = FMOD_System_Update(sfxSystem);
  ERRCHECK(result);
}

// Cleanup the Audio System
void Audio_cleanup()
{
	// Release all sounds that have been created
	result = FMOD_Sound_Release(bgmGameplay);
	ERRCHECK(result);

	// Close and Release the FMOD system
	result = FMOD_System_Close(soundSystem);
	ERRCHECK(result);
	result = FMOD_System_Release(soundSystem);
	ERRCHECK(result);
}

////////////////////////////////////////////////////////////////////
void Audio_playGameplay()
{
  result = FMOD_System_CreateStream(soundSystem, "./Assets/Audio/Penguin.mp3", FMOD_LOOP_NORMAL | FMOD_2D, 0, &bgmGameplay);
  ERRCHECK(result);

  result = FMOD_System_PlaySound(soundSystem, bgmGameplay, 0, false, &MusicChannel);
  ERRCHECK(result);
}

void Audio_stopGameplay() {
    FMOD_Channel_Stop(MusicChannel);
    FMOD_Channel_Stop(SFXChannel);
}

void Audio_playSfxHitWall()
{
  result = FMOD_System_CreateStream(sfxSystem, "./Assets/Audio/sfx.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &sfxPlayerHitWall);
  ERRCHECK(result);

  result = FMOD_System_PlaySound(sfxSystem, sfxPlayerHitWall, 0, false, &SFXChannel);
  ERRCHECK(result);
}

void Audio_playSfxPolarGrowl()
{
  result = FMOD_System_CreateStream(sfxSystem, "./Assets/Audio/SFX/PolarGrowl.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &sfxPlayerHitWall);
  ERRCHECK(result);

  result = FMOD_System_PlaySound(sfxSystem, sfxPlayerHitWall, 0, false, &SFXChannel);
  ERRCHECK(result);
}

void Audio_playSfxReady()
{
  result = FMOD_System_CreateStream(sfxSystem, "./Assets/Audio/SFX/Ready.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &sfxPlayerHitWall);
  ERRCHECK(result);

  result = FMOD_System_PlaySound(sfxSystem, sfxPlayerHitWall, 0, false, &SFXChannel);
  ERRCHECK(result);
}

void Audio_playSfxSet()
{
  result = FMOD_System_CreateStream(sfxSystem, "./Assets/Audio/SFX/Set.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &sfxPlayerHitWall);
  ERRCHECK(result);

  result = FMOD_System_PlaySound(sfxSystem, sfxPlayerHitWall, 0, false, &SFXChannel);
  ERRCHECK(result);
}

void Audio_playSfxGo()
{
  result = FMOD_System_CreateStream(sfxSystem, "./Assets/Audio/SFX/Go.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &sfxPlayerHitWall);
  ERRCHECK(result);

  result = FMOD_System_PlaySound(sfxSystem, sfxPlayerHitWall, 0, false, &SFXChannel);
  ERRCHECK(result);
}