/**
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

                                                //1234    12345678901234567890    12345
char* leaderboardHeader[LEADERBOARD_COLUMNS] = { "Rank", "Name                ", "Time " };
char* leaderboardFormat[LEADERBOARD_COLUMNS] = { "%2i  ", "%-20s", "%2.2i:%2.2i" };

typedef struct Leaderboard {
	unsigned camNum;
	AEGfxTexture* font;
	AEVec2 nextPos;
	AEVec2 posDiff;
	AEVec2 charScale;
	Color palatte[LEADERBOARD_PALETTE_ROWS][LEADERBOARD_PALETTE_COLUMNS];
	Object* textObj[LEADERBOARD_SIZE + 1][LEADERBOARD_COLUMNS];
	char leaderboardText[LEADERBOARD_SIZE + 1][LEADERBOARD_COLUMNS][LEADERBOARD_NAME_LENGTH];
	int yourRank;
	int ranksToDisplay;
	int ranksBeingDisplayed;
	float addRankTime;
	float timeUntilNextRank;
} Leaderboard;

static void Leaderboard_onInit(Object* obj, Leaderboard* data)
{
	printf("Leaderboard init\n");

	AEVec2 textPos = data->nextPos;
	unsigned camNum = data->camNum;


	data->textObj[0][LEADERBOARD_RANK_INDEX] = Text_new(leaderboardHeader[LEADERBOARD_RANK_INDEX],
		data->font, textPos, data->charScale.x, data->charScale.y,
		data->palatte[LEADERBOARD_PALETTE_RANK_INDEX][LEADERBOARD_PALETTE_HEADER_INDEX], camNum);

	textPos.x += LEADERBOARD_RANK_LENGTH * (data->charScale.x);

	data->textObj[0][LEADERBOARD_NAME_INDEX] = Text_new(leaderboardHeader[LEADERBOARD_NAME_INDEX],
		data->font, textPos, data->charScale.x, data->charScale.y,
		data->palatte[LEADERBOARD_PALETTE_NAME_INDEX][LEADERBOARD_PALETTE_HEADER_INDEX], camNum);

	textPos.x += LEADERBOARD_NAME_LENGTH * (data->charScale.x);

	data->textObj[0][LEADERBOARD_TIME_INDEX] = Text_new(leaderboardHeader[LEADERBOARD_TIME_INDEX],
		data->font, textPos, data->charScale.x, data->charScale.y,
		data->palatte[LEADERBOARD_PALETTE_TIME_INDEX][LEADERBOARD_PALETTE_HEADER_INDEX], camNum);

	ObjectManager_addObj(data->textObj[0][LEADERBOARD_RANK_INDEX]);
	ObjectManager_addObj(data->textObj[0][LEADERBOARD_NAME_INDEX]);
	ObjectManager_addObj(data->textObj[0][LEADERBOARD_TIME_INDEX]);

	data->nextPos.x += data->posDiff.x;
	data->nextPos.y -= data->posDiff.y;

	UNREFERENCED_PARAMETER(obj);
}

static void Leaderboard_onUpdate(Object* obj, Leaderboard* data, float dt)
{
	printf("Leaderboard update\n");

	if (data->ranksBeingDisplayed < data->ranksToDisplay)
	{
		LeaderboardRank rank = Leaderboard_getEntry(data->ranksBeingDisplayed);

		if (rank.time > 0)
		{
			data->timeUntilNextRank -= dt;

			if (data->timeUntilNextRank < 0)
			{
				sprintf_s(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_RANK_INDEX],
					LEADERBOARD_RANK_LENGTH, leaderboardFormat[LEADERBOARD_RANK_INDEX], data->ranksBeingDisplayed + 1);
				sprintf_s(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_NAME_INDEX],
					LEADERBOARD_NAME_LENGTH, leaderboardFormat[LEADERBOARD_NAME_INDEX], rank.name);
				sprintf_s(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_TIME_INDEX],
					LEADERBOARD_TIME_LENGTH, leaderboardFormat[LEADERBOARD_TIME_INDEX], rank.minutes, rank.seconds);


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
						data->palatte[LEADERBOARD_PALETTE_RANK_INDEX][paleteRowIndex], camNum);

				textPos.x += LEADERBOARD_RANK_LENGTH * (data->charScale.x);

				data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_NAME_INDEX] =
					Text_new(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_NAME_INDEX],
						data->font, textPos, data->charScale.x, data->charScale.y,
						data->palatte[LEADERBOARD_PALETTE_NAME_INDEX][paleteRowIndex], camNum);

				textPos.x += LEADERBOARD_NAME_LENGTH * (data->charScale.x);

				data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_TIME_INDEX] =
					Text_new(data->leaderboardText[data->ranksBeingDisplayed + 1][LEADERBOARD_TIME_INDEX],
						data->font, textPos, data->charScale.x, data->charScale.y,
						data->palatte[LEADERBOARD_PALETTE_TIME_INDEX][paleteRowIndex], camNum);

				ObjectManager_addObj(data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_RANK_INDEX]);
				ObjectManager_addObj(data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_NAME_INDEX]);
				ObjectManager_addObj(data->textObj[data->ranksBeingDisplayed + 1][LEADERBOARD_TIME_INDEX]);

				data->timeUntilNextRank = data->addRankTime;
				data->ranksBeingDisplayed++;
				data->nextPos.x += data->posDiff.x;
				data->nextPos.y -= data->posDiff.y;
			}
		}
	}

	UNREFERENCED_PARAMETER(obj);
}

static void Leaderboard_onDraw(Object* obj, Leaderboard* data)
{
	// Nothing to draw except text which is drawn by the text handeler
	UNREFERENCED_PARAMETER(obj);
	UNREFERENCED_PARAMETER(data);
}

Object* Leaderboard_new(AEGfxTexture* font, AEVec2 pos, AEVec2 posDiff, AEVec2 charScale, 
		Color palatte[LEADERBOARD_PALETTE_ROWS][LEADERBOARD_PALETTE_COLUMNS], 
		int yourRank, int ranksToDisplay, float addRankTime, unsigned camNum)
{
	Leaderboard* leaderboard = calloc(1, sizeof(Leaderboard));

	leaderboard->font = font;
	leaderboard->nextPos = pos;
	leaderboard->posDiff = posDiff;
	leaderboard->charScale = charScale;
	leaderboard->yourRank = yourRank;
	leaderboard->ranksToDisplay = ranksToDisplay;
	leaderboard->ranksBeingDisplayed = 0;
	leaderboard->addRankTime = addRankTime;
	leaderboard->timeUntilNextRank = addRankTime;
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

void Default_Leaderboard(unsigned camNum)
{
	Color palette[LEADERBOARD_PALETTE_ROWS][LEADERBOARD_PALETTE_COLUMNS] = {
			{ { 1, 1, 1, 1, }, { 1, 1, 1, 1, }, { 1, 1, 1, 1, } },
			{ { 1, 1, 1, 1, }, { 1, 1, 1, 1, }, { 1, 1, 1, 1, } },
			{ { 1, 1, 1, 1, }, { 1, 1, 1, 1, }, { 1, 1, 1, 1, } } };

	Object* leaderboard = Leaderboard_new(TEXTURES.font, 
		(AEVec2) { -375, 275 }, (AEVec2) { 5, 45 }, (AEVec2) { 23, 42 }, palette, 0, 10, 0.2f, camNum);
	Object* titleScreenButton = Button_new(
		titleScreenEffect, TEXTURES.endScreen_titleScreenButton, TEXTURES.buttonSelected, TEXTURES.endScreen_titleScreenButton,
		0, -300, 600, 100, camNum);

	ObjectManager_addObj(leaderboard);
	ObjectManager_addObj(titleScreenButton);
}