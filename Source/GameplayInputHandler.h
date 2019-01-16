/**
 * @file GameplayInputHandler.h
 * @author Richard Folorunso
 * @date 2019/01/09
 * @brief Handles user input durring gameplay.
 */
// Copyright © 2019 DigiPen (USA) Corporation.

#pragma once
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/* Changes the controls. */
void GameplayInput_ChangeControls(char NewLeft, char NewRight, char NewUp, 
                                  char NewDown, char NewA, char NewB, 
                                  char NewC);

/* Checks to see if the left key is held down or not. */
int GameplayInput_LeftCheck(void);

/* Checks to see if the left key has been pressed or not. */
int GameplayInput_LeftCheckPressed(void);

/* Checks to see if the left key has been released or not. */
int GameplayInput_LeftCheckReleased(void);

/* Checks to see if the Right key is held down or not. */
int GameplayInput_RightCheck(void);

/* Checks to see if the Right key has been pressed or not. */
int GameplayInput_RightCheckPressed(void);

/* Checks to see if the Right key has been released or not. */
int GameplayInput_RightCheckReleased(void);

/* Checks to see if the Up key is held down or not. */
int GameplayInput_UpCheck(void);

/* Checks to see if the Up key has been pressed or not. */
int GameplayInput_UpCheckPressed(void);

/* Checks to see if the Up key has been released or not. */
int GameplayInput_UpCheckReleased(void);

/* Checks to see if the Down key is held down or not. */
int GameplayInput_DownCheck(void);

/* Checks to see if the Down key has been pressed or not. */
int GameplayInput_DownCheckPressed(void);

/* Checks to see if the Down key has been released or not. */
int GameplayInput_DownCheckReleased(void);