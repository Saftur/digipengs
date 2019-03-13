/**
 * @file InputHandler.c
 * @author Richard Folorunso
 * @date 2019/01/09
 * @brief Handles user input durring gameplay.
 */
// Copyright © 2019 DigiPen (USA) Corporation.

#include "stdafx.h" // Should be included first in every .c file!

#include "AEEngine.h"
#include "InputHandler.h"
#include <xinput.h>

static int Input_gamepadInit(Controls *ctrls, int Directions)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if (XInputGetState(ctrls->gamepad, &state) == ERROR_SUCCESS)
	{
		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);
		
		if (Directions == -1 && normLX < -0.25)
		{
			return 1;
		}

		if (Directions == 1 && normLX > 0.25)
		{
			return 1;
		}

		if (Directions == -10 && normLY < -0.25)
		{
			return 1;
		}
	}

	return 0;
}
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/**************************************************************************
   Function: Input_leftCheck

Description: Checks to see if the left key is held down or not.

     Inputs: N/A

    Outputs: Returns true (1) as long as the left key is held down.
**************************************************************************/
int Input_leftCheck(Controls ctrls)
{
  return AEInputCheckCurr(ctrls.left) || Input_gamepadInit(&ctrls, -1);
}

/**************************************************************************
   Function: Input_leftCheckPressed

Description: Checks to see if the left key has been pressed or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the left key
             was pressed.
**************************************************************************/
int Input_leftCheckPressed(Controls ctrls)
{
  return AEInputCheckTriggered(ctrls.left);
}

/**************************************************************************
   Function: Input_leftCheckReleased

Description: Checks to see if the left key has been released or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the left key
             was released.
**************************************************************************/
int Input_leftCheckReleased(Controls ctrls)
{
  return AEInputCheckReleased(ctrls.left);
}

/**************************************************************************
   Function: Input_rightCheck

Description: Checks to see if the Right key is held down or not.

     Inputs: N/A

    Outputs: Returns true (1) as long as the Right key is held down.
**************************************************************************/
int Input_rightCheck(Controls ctrls)
{
  return AEInputCheckCurr(ctrls.right) || Input_gamepadInit(&ctrls, 1);
}

/**************************************************************************
   Function: Input_rightCheckPressed

Description: Checks to see if the Right key has been pressed or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Right key
             was pressed.
**************************************************************************/
int Input_rightCheckPressed(Controls ctrls)
{
  return AEInputCheckTriggered(ctrls.right);
}

/**************************************************************************
   Function: Input_rightCheckReleased

Description: Checks to see if the Right key has been released or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Right key
             was released.
**************************************************************************/
int Input_rightCheckReleased(Controls ctrls)
{
  return AEInputCheckReleased(ctrls.right);
}

/**************************************************************************
   Function: Input_upCheck

Description: Checks to see if the Up key is held down or not.

     Inputs: N/A

    Outputs: Returns true (1) as long as the Up key is held down.
**************************************************************************/
int Input_upCheck(Controls ctrls)
{
  return AEInputCheckCurr(ctrls.up);
}

/**************************************************************************
   Function: Input_upCheckPressed

Description: Checks to see if the Up key has been pressed or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Up key
             was pressed.
**************************************************************************/
int Input_upCheckPressed(Controls ctrls)
{
  return AEInputCheckTriggered(ctrls.up);
}

/**************************************************************************
   Function: Input_upCheckReleased

Description: Checks to see if the Up key has been released or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Up key
             was released.
**************************************************************************/
int Input_upCheckReleased(Controls ctrls)
{
  return AEInputCheckReleased(ctrls.up);
}

/**************************************************************************
   Function: Input_downCheck

Description: Checks to see if the Down key is held down or not.

     Inputs: N/A

    Outputs: Returns true (1) as long as the Down key is held down.
**************************************************************************/
int Input_downCheck(Controls ctrls)
{
  return AEInputCheckCurr(ctrls.down) || Input_gamepadInit(&ctrls, -10);
}

/**************************************************************************
   Function: Input_downCheckPressed

Description: Checks to see if the Down key has been pressed or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Down key
             was pressed.
**************************************************************************/
int Input_downCheckPressed(Controls ctrls)
{
  return AEInputCheckTriggered(ctrls.down);
}

/**************************************************************************
   Function: Input_downCheckReleased

Description: Checks to see if the Down key has been released or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Down key
             was released.
**************************************************************************/
int Input_downCheckReleased(Controls ctrls)
{
  return AEInputCheckReleased(ctrls.down);
}