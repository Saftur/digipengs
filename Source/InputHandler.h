/**
 * @file InputHandler.h
 * @author Richard Folorunso
 * @date 2019/01/09
 * @brief Handles user input durring gameplay.
 */
// Copyright © 2019 DigiPen (USA) Corporation.

#pragma once

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

typedef struct Controls {
unsigned char left;
unsigned char right;
unsigned char up;
unsigned char down;
unsigned int gamepad;
} Controls;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/* Checks to see if the Left key is held down or not. */
int Input_leftCheck(Controls ctrls);

/* Checks to see if the Left key has been pressed or not. */
int Input_leftCheckPressed(Controls ctrls);

/* Checks to see if the Left key has been released or not. */
int Input_leftCheckReleased(Controls ctrls);

/* Checks to see if the Right key is held down or not. */
int Input_rightCheck(Controls ctrls);

/* Checks to see if the Right key has been pressed or not. */
int Input_rightCheckPressed(Controls ctrls);

/* Checks to see if the Right key has been released or not. */
int Input_rightCheckReleased(Controls ctrls);

/* Checks to see if the Up key is held down or not. */
int Input_upCheck(Controls ctrls);

/* Checks to see if the Up key has been pressed or not. */
int Input_upCheckPressed(Controls ctrls);

/* Checks to see if the Up key has been released or not. */
int Input_upCheckReleased(Controls ctrls);

/* Checks to see if the Down key is held down or not. */
int Input_downCheck(Controls ctrls);

/* Checks to see if the Down key has been pressed or not. */
int Input_downCheckPressed(Controls ctrls);

/* Checks to see if the Down key has been released or not. */
int Input_downCheckReleased(Controls ctrls);