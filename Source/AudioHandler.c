/**
 * @file AudioHandler.c
 * @author Richard Folorunso
 * @date 2019/01/09
 * @brief Handles user input durring gameplay.
 */
// Copyright © 2019 DigiPen (USA) Corporation.

#include "stdafx.h" // Should be included first in every .c file!

#include "AudioHandler.h"
#include "fmod.h"
#include <stdio.h>		// printf()
#include <stdbool.h>	// FALSE

FMOD_SYSTEM *soundSystem;
FMOD_CHANNEL *channel = 0;
FMOD_RESULT result;

// Contains all the music/soundeffects in the game
FMOD_SOUND *bgmGameplay;
FMOD_SOUND *sfxPlayerSlide;

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

	void *extradriverdata = 0;
	result = FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, extradriverdata);
	ERRCHECK(result);
}

// Update the Audio System
// Note: this should be called frequently such as every game loop or
//       every time a user enters a command depending on the engine
void AudioUpdate()
{
	result = FMOD_System_Update(soundSystem);
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
  // Create and Play the sound
  // Note: this should be generalized for multiple sounds and
  //       be placed in a function to be used outside of init.
  result = FMOD_System_CreateStream(soundSystem, "./Assets/Audio/OriginalMusic.mp3", FMOD_LOOP_NORMAL | FMOD_2D, 0, &bgmGameplay);
  ERRCHECK(result);

  result = FMOD_System_PlaySound(soundSystem, bgmGameplay, 0, false, &channel);
  ERRCHECK(result);
}

void Audio_stopGameplay() {
    FMOD_Channel_Stop(channel);
}
