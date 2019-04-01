/**
 * @file LevelEditor_HelpMenu.h
 * @author Connor Meyers
 * @date 2019/01/23
 * @brief Object implementation for the help menu
 */

#include "stdafx.h"

#include "LevelEditor_HelpMenu.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Object.h"
#include "objectmanager.h"

#define HELP_TEXTURE TEXTURES.le_helpMenu
#define MENU_TEXTURE TEXTURES.le_fullMenu

#define ASP_X 5.19512194f 
#define H_ASP_Y 1.0f
#define F_ASP_Y 10.2408536f

#define SCL_X 64
#define SCL_Y 64
#define ALPHA 0.75
#define POS_X 770
#define POS_Y 500

static bool visible = false;
static Object *menu = NULL;

void LevelEditor_HelpMenu_toggle()
{
	visible = !visible;
}

void LevelEditor_HelpMenu_onDraw(Object *obj, void *data)
{
	UNREFERENCED_PARAMETER(data);
	AEGfxTexture *texture = visible ? MENU_TEXTURE : HELP_TEXTURE;
	float scaleX = SCL_X * ASP_X;
	float scaleY = SCL_Y * (visible ? F_ASP_Y : H_ASP_Y);
	AEVec2 pos;
	AEVec2Set(&pos, Object_getPos(obj).x, visible ? Object_getPos(obj).y + (SCL_Y * H_ASP_Y)/2 - scaleY / 2: Object_getPos(obj).y);
	ImageHandler_screenDrawTexture(MeshHandler_getSquareMesh(), texture, pos, scaleX, scaleY, 0, ALPHA);
}

void LevelEditor_HelpMenu_free(void *data)
{
	UNREFERENCED_PARAMETER(data);
	menu = NULL;
}

void LevelEditor_HelpMenu_init()
{
	if (menu)return;

	AEVec2 pos;
	AEVec2Set(&pos, POS_X, POS_Y);
	menu = Object_new(NULL, NULL, LevelEditor_HelpMenu_onDraw, NULL, LevelEditor_HelpMenu_free, "HelpMenu");
	Object_setPos(menu, pos);

	ObjectManager_addObj(menu);
}
