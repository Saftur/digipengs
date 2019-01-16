/**
 * @file GameplayInputHandler.c
 * @author Richard Folorunso
 * @date 2019/01/09
 * @brief Handles user input durring gameplay.
 */
// Copyright © 2019 DigiPen (USA) Corporation.

#include "stdafx.h" // Should be included first in every .c file!

#include "AEEngine.h"
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static unsigned char Left = 0x25;
static unsigned char Right = 0x27;
static unsigned char Up = 0x26;
static unsigned char Down = 0x28;
static unsigned char A  = 'A';
static unsigned char B = 'Z';
static unsigned char C = 'X';

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/**************************************************************************
   Function: GameplayInput_ChangeControls

Description: Changes the controls.

     Inputs: unsigned chars

    Outputs: N/A
**************************************************************************/
void GameplayInput_ChangeControls(char NewLeft, char NewRight, char NewUp, 
                             char NewDown, char NewA, char NewB, 
                             char NewC)
{
  Left = NewLeft;
  Right = NewRight;
  Up = NewUp;
  Down = NewDown;
  A  = NewA;
  B = NewB;
  C = NewC;
}

/**************************************************************************
   Function: GameplayInput_LeftCheck

Description: Checks to see if the left key is held down or not.

     Inputs: N/A

    Outputs: Returns true (1) as long as the left key is held down.
**************************************************************************/
int GameplayInput_LeftCheck(void)
{
  return (AEInputCheckCurr(Left));
}

/**************************************************************************
   Function: GameplayInput_LeftCheckPressed

Description: Checks to see if the left key has been pressed or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the left key
             was pressed.
**************************************************************************/
int GameplayInput_LeftCheckPressed(void)
{
  return (AEInputCheckTriggered(Left));
}

/**************************************************************************
   Function: GameplayInput_LeftCheckReleased

Description: Checks to see if the left key has been released or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the left key
             was released.
**************************************************************************/
int GameplayInput_LeftCheckReleased(void)
{
  return (AEInputCheckReleased(Left));
}

/**************************************************************************
   Function: GameplayInput_RightCheck

Description: Checks to see if the Right key is held down or not.

     Inputs: N/A

    Outputs: Returns true (1) as long as the Right key is held down.
**************************************************************************/
int GameplayInput_RightCheck(void)
{
  return (AEInputCheckCurr(Right));
}

/**************************************************************************
   Function: GameplayInput_RightCheckPressed

Description: Checks to see if the Right key has been pressed or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Right key
             was pressed.
**************************************************************************/
int GameplayInput_RightCheckPressed(void)
{
  return (AEInputCheckTriggered(Right));
}

/**************************************************************************
   Function: GameplayInput_RightCheckReleased

Description: Checks to see if the Right key has been released or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Right key
             was released.
**************************************************************************/
int GameplayInput_RightCheckReleased(void)
{
  return (AEInputCheckReleased(Right));
}

/**************************************************************************
   Function: GameplayInput_UpCheck

Description: Checks to see if the Up key is held down or not.

     Inputs: N/A

    Outputs: Returns true (1) as long as the Up key is held down.
**************************************************************************/
int GameplayInput_UpCheck(void)
{
  return (AEInputCheckCurr(Up));
}

/**************************************************************************
   Function: GameplayInput_UpCheckPressed

Description: Checks to see if the Up key has been pressed or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Up key
             was pressed.
**************************************************************************/
int GameplayInput_UpCheckPressed(void)
{
  return (AEInputCheckTriggered(Up));
}

/**************************************************************************
   Function: GameplayInput_UpCheckReleased

Description: Checks to see if the Up key has been released or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Up key
             was released.
**************************************************************************/
int GameplayInput_UpCheckReleased(void)
{
  return (AEInputCheckReleased(Up));
}

/**************************************************************************
   Function: GameplayInput_DownCheck

Description: Checks to see if the Down key is held down or not.

     Inputs: N/A

    Outputs: Returns true (1) as long as the Down key is held down.
**************************************************************************/
int GameplayInput_DownCheck(void)
{
  return (AEInputCheckCurr(Down));
}

/**************************************************************************
   Function: GameplayInput_DownCheckPressed

Description: Checks to see if the Down key has been pressed or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Down key
             was pressed.
**************************************************************************/
int GameplayInput_DownCheckPressed(void)
{
  return (AEInputCheckTriggered(Down));
}

/**************************************************************************
   Function: GameplayInput_DownCheckReleased

Description: Checks to see if the Down key has been released or not.

     Inputs: N/A

    Outputs: Returns true (1) only on the first frame the Down key
             was released.
**************************************************************************/
int GameplayInput_DownCheckReleased(void)
{
  return (AEInputCheckReleased(Down));
}