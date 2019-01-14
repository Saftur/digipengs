// ---------------------------------------------------------------------------
// Project Name		:	Simple Demo
// File Name		:	Main.c
// Author			:	Antoine Abi Chacra
// Creation Date	:	2012/01/11
// Purpose			:	Demonstrates Alpha Engine features.
// History			:
// - 2012/01/11		:	- initial implementation
// - 2019/01/04		:	- Fixed AE_ASSERT/AE_WARNING issues.
// - 2019/01/06		:	- Added missing call to AESysUpdate().
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes

#include "stdafx.h"		// Should be included first in every .c file!

#include <AEEngine.h>
#include "LevelManager.h"
#include "objectmanager.h"

// ---------------------------------------------------------------------------

// Libraries
#ifdef _DEBUG
#pragma comment (lib, "Alpha_Engine_D.lib")
#else
#pragma comment (lib, "Alpha_Engine.lib")
#endif

// ---------------------------------------------------------------------------
// globals

int gGameRunning = 1;

// ---------------------------------------------------------------------------
// Static function protoypes

// ---------------------------------------------------------------------------
// main


int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(prevInstanceH);

	// Initialize the system 
	AESysInitInfo sysInitInfo;
	sysInitInfo.mCreateWindow = 1;
	sysInitInfo.mAppInstance = instanceH;
	sysInitInfo.mShow = show;
	sysInitInfo.mWinWidth = 800;
	sysInitInfo.mWinHeight = 600;
	sysInitInfo.mCreateConsole = 1;
	sysInitInfo.mMaxFrameRate = 60;
	sysInitInfo.mpWinCallBack = NULL;//MyWinCallBack;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
	sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;//WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;;	
	sysInitInfo.mWindowHandle = NULL;
	sysInitInfo.mHandleWindowMessages = 1;
	AESysInit(&sysInitInfo);

	// reset the system modules
    AESysReset();

    //Dt variables
    float dt = 0.0167f;
    DWORD lastTime = 0;
    DWORD currentTime = GetTickCount();

    LevelManagerInit();
	ObjectManager_init();

	// Game Loop
	while (LevelManagerIsRunning())
	{

		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

        //Calculate dt
        currentTime = GetTickCount();
        if (lastTime > 0) dt = (float) (currentTime - lastTime)/1000;
        lastTime = currentTime;

        LevelManagerUpdate(dt);

		ObjectManager_update();

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
        if (AEInputCheckTriggered(VK_ESCAPE) || 0 == AESysDoesWindowExist())
            LevelManagerSetNextLevel(LevelQuit);
	}

	ObjectManager_end();

	// free the system
	AESysExit();

	return 1;
}

// ---------------------------------------------------------------------------

