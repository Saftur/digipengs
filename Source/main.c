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
#include "ObjectManager.h"
#include "Boulder.h"
#include "ImageHandler.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "MeshHandler.h"
#include "AudioHandler.h"
#include "Utils.h"

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

    //srand((int)time(NULL));
    srand(20);

    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

	// Initialize the system 
	AESysInitInfo sysInitInfo;
	sysInitInfo.mCreateWindow = 1;
	sysInitInfo.mAppInstance = instanceH;
	sysInitInfo.mShow = show;
    sysInitInfo.mWinWidth = desktop.right;// 800;
    sysInitInfo.mWinHeight = desktop.bottom;// 600;
	sysInitInfo.mCreateConsole = 1;
	sysInitInfo.mMaxFrameRate = 60;
	sysInitInfo.mpWinCallBack = NULL;//MyWinCallBack;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
    sysInitInfo.mWindowStyle = WS_POPUP;//WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;;	
	sysInitInfo.mWindowHandle = NULL;
	sysInitInfo.mHandleWindowMessages = 1;
	AESysInit(&sysInitInfo);

	// reset the system modules
    AESysReset();

    const HWND hwnd = AESysGetWindowHandle();

    /*SetWindowLong(hwnd, GWL_STYLE,
                  ~(WS_CAPTION | WS_THICKFRAME));*/
    SetWindowLong(hwnd, GWL_EXSTYLE, 0);

    /*RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, desktop.right, desktop.bottom, SWP_SHOWWINDOW);*/
    SetWindowPos(hwnd, HWND_TOP, 0, 0, desktop.right, desktop.bottom, SWP_SHOWWINDOW);

    //Dt variables
    float dt = 0.0167f;
    DWORD lastTime = 0;
    DWORD currentTime = GetTickCount();

    CollisionHandler_Init();
    LevelManager_init();
	ObjectManager_init();
	ImageHandler_initializeTextures();
	Camera_init();
    Audio_init();

    AEGfxSetBackgroundColor(0.4f, 0.4f, 0.4f);
    
    Camera_new((AEVec2) { 0, 0 }, 1.f, 0, (AEVec2) { 0, 0 }, AEGfxGetWinSize());

    //AEInputShowCursor(0); //Hide the cursor.

	// Game Loop
	while (LevelManager_isRunning())
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

        //Calculate dt
        currentTime = GetTickCount();
        //if (lastTime > 0) dt = (float) (currentTime - lastTime)/1000;
        lastTime = currentTime;

        LevelManager_update(dt);

		ObjectManager_update(dt);

        CollisionHandler_Update(dt);

		for (unsigned i = 0; i < Camera_count(); i++) {
			Camera_set(i);
            LevelManager_draw();
			ObjectManager_draw();
		}

		// Informing the system about the loop's end
		AESysFrameEnd();
        if (AEInputCheckTriggered(VK_ESCAPE)) LevelManager_setNextLevel(TitleScreen);
		// check if forcing the application to quit
        if (0 == AESysDoesWindowExist()) LevelManager_setNextLevel(LevelQuit);
	}

	ObjectManager_shutdown();
	ImageHandler_shutdown();
	Camera_shutdown();
    AEGfxMeshFree(MeshHandler_getSquareMesh());
    Audio_cleanup();

	// free the system
	AESysExit();

	return 1;
}

// ---------------------------------------------------------------------------

