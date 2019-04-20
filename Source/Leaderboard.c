/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file Leaderboard.c
 * @author Parker Friedland
 * @date 3/31/2019
 * @brief Leaderboard
 */

#include "stdafx.h"
#include "Leaderboard.h"
#include "TextHandler.h"
#include "ImageHandler.h"
#include "ObjectManager.h"
#include "LeaderboardData.h"
#include "Camera.h"
#include "Button.h"
#include "LevelManager.h"
#include "Level2.h"

                                                //1234    12345678901234567890    12345
char* leaderboardHeader[LEADERBOARD_COLUMNS] = { "Rank", "Name                ", "Time " };
char* leaderboardFormat[LEADERBOARD_COLUMNS] = { "%2i  ", "%-20s", "%2.2i:%2.2i" };

typedef struct Leaderboard 
{
	unsigned camNum;
	AEGfxTexture* font;
	AEVec2 nextPos;
	AEVec2 posDiff1;
	AEVec2 posDiff2;
	AEVec2 charScale;
	Color palatte[LEADERBOARD_PALETTE_ROWS][LEADERBOARD_PALETTE_COLUMNS];
	Object* textObj[LEADERBOARD_SIZE + 1][LEADERBOARD_COLUMNS];
	char leaderboardText[LEADERBOARD_SIZE + 1][LEADERBOARD_COLUMNS][LEADERBOARD_NAME_LENGTH];
	int yourRank;
	int ranksToDisplay;
	int ranksBeingDisplayed;
	float addRankTime;
	float timeUntilNextRank;
	bool typingName;
	int nameIndex;
	char* name;
} Leaderboard;

static void Leaderboard_onInit(Object* obj, Leaderboard* data)
{
	printf("Leaderboard init\n");

	AEVec2 textPos = data->nextPos;
	unsigned camNum = data->camNum;


	data->textObj[0][LEADERBOARD_RANK_INDEX] = Text_new(leaderboardHeader[LEADERBOARD_RANK_INDEX],
		data->font, textPos, data->charScale.x, data->charScale.y,
		data->palatte[LEADERBOARD_PALETTE_HEADER_INDEX][LEADERBOARD_PALETTE_RANK_INDEX], camNum);

	textPos.x += LEADERBOARD_RANK_LENGTH * (data->charScale.x);
	textPos.x += data->posDiff1.x;
	textPos.y += data->posDiff1.y;

	data->textObj[0][LEADERBOARD_NAME_INDEX] = Text_new(leaderboardHeader[LEADERBOARD_NAME_INDEX],
		data->font, textPos, data->charScale.x, data->charScale.y,
		data->palatte[LEADERBOARD_PALETTE_HEADER_INDEX][LEADERBOARD_PALETTE_NAME_INDEX], camNum);

	textPos.x += LEADERBOARD_NAME_LENGTH * (data->charScale.x);
	textPos.x += data->posDiff1.x;
	textPos.y += data->posDiff1.y;

	data->textObj[0][LEADERBOARD_TIME_INDEX] = Text_new(leaderboardHeader[LEADERBOARD_TIME_INDEX],
		data->font, textPos, data->charScale.x, data->charScale.y,
		data->palatte[LEADERBOARD_PALETTE_HEADER_INDEX][LEADERBOARD_PALETTE_TIME_INDEX], camNum);

	ObjectManager_addObj(data->textObj[0][LEADERBOARD_RANK_INDEX]);
	ObjectManager_addObj(data->textObj[0][LEADERBOARD_NAME_INDEX]);
	ObjectManager_addObj(data->textObj[0][LEADERBOARD_TIME_INDEX]);

	data->nextPos.x += data->posDiff2.x;
	data->nextPos.y -= data->posDiff2.y;

	UNREFERENCED_PARAMETER(obj);
}

static void AddNextLeaderboardRank(Leaderboard* data, LeaderboardRank* rank)
{
	sprintf_s(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_RANK_INDEX],
		LEADERBOARD_RANK_LENGTH, leaderboardFormat[LEADERBOARD_RANK_INDEX], data->ranksBeingDisplayed + 1);
	sprintf_s(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_NAME_INDEX],
		LEADERBOARD_NAME_LENGTH, leaderboardFormat[LEADERBOARD_NAME_INDEX], rank->name);
	sprintf_s(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_TIME_INDEX],
		LEADERBOARD_TIME_LENGTH, leaderboardFormat[LEADERBOARD_TIME_INDEX], rank->minutes, rank->seconds);

	int paleteRowIndex = LEADERBOARD_PALETTE_LEADERBOARD_INDEX;
	if (data->ranksBeingDisplayed + 1 == data->yourRank)
	{
		paleteRowIndex = LEADERBOARD_PALETTE_YOUR_RANK_INDEX;
	}

	AEVec2 textPos = data->nextPos;
	unsigned camNum = data->camNum;

	data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_RANK_INDEX] =
		Text_new(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_RANK_INDEX],
			data->font, textPos, data->charScale.x, data->charScale.y,
			data->palatte[paleteRowIndex][LEADERBOARD_PALETTE_RANK_INDEX], camNum);

	textPos.x += LEADERBOARD_RANK_LENGTH * (data->charScale.x);
	textPos.x += data->posDiff1.x;
	textPos.y += data->posDiff1.y;

	data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_NAME_INDEX] =
		Text_new(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_NAME_INDEX],
			data->font, textPos, data->charScale.x, data->charScale.y,
			data->palatte[paleteRowIndex][LEADERBOARD_PALETTE_NAME_INDEX], camNum);

	textPos.x += LEADERBOARD_NAME_LENGTH * (data->charScale.x);
	textPos.x += data->posDiff1.x;
	textPos.y += data->posDiff1.y;

	data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_TIME_INDEX] =
		Text_new(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_TIME_INDEX],
			data->font, textPos, data->charScale.x, data->charScale.y,
			data->palatte[paleteRowIndex][LEADERBOARD_PALETTE_TIME_INDEX], camNum);

	ObjectManager_addObj(data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_RANK_INDEX]);
	ObjectManager_addObj(data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_NAME_INDEX]);
	ObjectManager_addObj(data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_TIME_INDEX]);

	data->timeUntilNextRank = data->addRankTime;
	data->ranksBeingDisplayed++;
	data->nextPos.x += data->posDiff2.x;
	data->nextPos.y -= data->posDiff2.y;
}

static void InsertingPlayerName(Leaderboard* data)
{
	for (u8 key = 'A'; key <= 'Z'; key++)
	{
		if (AEInputCheckTriggered(key))
		{
			if (data->nameIndex < LEADERBOARD_NAME_LENGTH - 1)
			{
				if (!(data->typingName))
				{
					for (int i = 0; i < LEADERBOARD_NAME_LENGTH; i++)
					{
						data->name[i] = 0;
					}

					data->typingName = true;
				}

				if (AEInputCheckCurr(VK_LSHIFT) || AEInputCheckCurr(VK_RSHIFT))
				{
					data->name[data->nameIndex++] = (char)key;
				}
				else
				{
					data->name[data->nameIndex++] = (char)key - 'A' + 'a';
				}
			}
		}
	}

	for (u8 key = '0'; key <= '9'; key++)
	{
		if (AEInputCheckTriggered(key))
		{
			if (data->nameIndex < LEADERBOARD_NAME_LENGTH - 1)
			{
				if (!(data->typingName))
				{
					for (int i = 0; i < LEADERBOARD_NAME_LENGTH; i++)
					{
						data->name[i] = 0;
					}

					data->typingName = true;
				}

				data->name[data->nameIndex++] = (char)key;
			}
		}
	}

	if (AEInputCheckTriggered('\b'))
	{
		if (!(data->typingName))
		{
			for (int i = 0; i < LEADERBOARD_NAME_LENGTH; i++)
			{
				data->name[i] = 0;
			}

			data->typingName = true;
		}

		if (data->nameIndex > 0)
		{
			data->name[--(data->nameIndex)] = 0;
		}
	}

	sprintf_s(data->leaderboardText[data->yourRank][LEADERBOARD_NAME_INDEX],
		LEADERBOARD_NAME_LENGTH, leaderboardFormat[LEADERBOARD_NAME_INDEX],
		Leaderboard_getEntry(data->yourRank)->name);
}

static void Leaderboard_onUpdate(Object* obj, Leaderboard* data, float dt)
{
	printf("Leaderboard update\n");

	if (data->ranksBeingDisplayed < data->ranksToDisplay)
	{
		LeaderboardRank* rank = Leaderboard_getEntry(data->ranksBeingDisplayed+1);

		if (rank->time > 0)
		{
			data->timeUntilNextRank -= dt;

			if (data->timeUntilNextRank < 0)
			{
				AddNextLeaderboardRank(data, rank);
			}
		}
	}

	if (data->yourRank)
	{
		keysEnabled = 0;
		InsertingPlayerName(data);
	}

	UNREFERENCED_PARAMETER(obj);
}

static void Leaderboard_onDraw(Object* obj, Leaderboard* data)
{
	// Nothing to draw except text which is drawn by the text handeler
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

Object* Leaderboard_new(AEGfxTexture* font, AEVec2 pos, AEVec2 posDiff1, AEVec2 posDiff2, AEVec2 charScale,
		Color palatte[LEADERBOARD_PALETTE_ROWS][LEADERBOARD_PALETTE_COLUMNS], 
		int yourRank, int ranksToDisplay, float addRankTime, unsigned camNum)
{
	Leaderboard* leaderboard = calloc(1, sizeof(Leaderboard));

	leaderboard->font = font;
	leaderboard->nextPos = pos;
	leaderboard->posDiff1 = posDiff1;
	leaderboard->posDiff2 = posDiff2;
	leaderboard->charScale = charScale;
	leaderboard->yourRank = yourRank;
	leaderboard->ranksToDisplay = ranksToDisplay;
	leaderboard->ranksBeingDisplayed = 0;
	leaderboard->addRankTime = addRankTime;
	leaderboard->timeUntilNextRank = addRankTime;
	leaderboard->typingName = false;
	leaderboard->name = Leaderboard_getEntry(yourRank)->name;
	leaderboard->camNum = camNum;

	for (int i = 0; i < LEADERBOARD_PALETTE_ROWS; i++)
	{
		for (int j = 0; j < LEADERBOARD_PALETTE_COLUMNS; j++)
		{
			leaderboard->palatte[i][j] = palatte[i][j];
		}
	}

	Object* leaderboardObj = Object_new(Leaderboard_onInit, Leaderboard_onUpdate, Leaderboard_onDraw, leaderboard, free, "Lap Counter");
	Object_setPos(leaderboardObj, pos);
	return leaderboardObj;
}

static void titleScreenEffect() {
	LevelManager_setNextLevel(TitleScreen);
}

Leaderboard* Default_Leaderboard(unsigned camNum, int yourRank)
{
	Color palette[LEADERBOARD_PALETTE_ROWS][LEADERBOARD_PALETTE_COLUMNS] = {
			{ { 1, 0, 0, 1, }, { 1, 0, 0, 1, }, { 1, 0, 0, 1, } },
			{ { 1, 0, 0, 1, }, { 1, 0, 0, 1, }, { 1, 0, 0, 1, } },
			{ { 1, 1, 0, 1, }, { 1, 1, 0, 1, }, { 1, 1, 0, 1, } } };

	Object* leaderboard = Leaderboard_new(TEXTURES.font, 
		(AEVec2) { -360, 275 }, (AEVec2) { 30, 0 }, (AEVec2) { 5, 45 }, (AEVec2) { 23, 42 }, palette, yourRank,
		LEADERBOARD_DEFAULT_NUM_RANKS_TO_DISPLAY, LEADERBOARD_DEFAULT_GROW_RATE, camNum);

	Object* titleScreenButton = Button_new(titleScreenEffect, 
		TEXTURES.endScreen_titleScreenButton, TEXTURES.buttonSelected, TEXTURES.endScreen_titleScreenButton,
		0, -300, 550, 95, 600, 100, 2.0f, 1.0f, camNum);

	ObjectManager_addObj(leaderboard);
	ObjectManager_addObj(titleScreenButton);

	return Object_getData(leaderboard);
}