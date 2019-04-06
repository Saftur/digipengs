#pragma once

#include <AEEngine.h>
#include "Object.h"
#include "ImageHandler.h"

#define LEADERBOARD_COLUMNS 3

#define LEADERBOARD_RANK_INDEX 0
#define LEADERBOARD_NAME_INDEX 1
#define LEADERBOARD_TIME_INDEX 2

#define LEADERBOARD_RANK_LENGTH 5
#define LEADERBOARD_NAME_LENGTH 21
#define LEADERBOARD_TIME_LENGTH 6

#define LEADERBOARD_PALETTE_ROWS 3
#define LEADERBOARD_PALETTE_COLUMNS 3

#define LEADERBOARD_PALETTE_RANK_INDEX 0
#define LEADERBOARD_PALETTE_NAME_INDEX 1
#define LEADERBOARD_PALETTE_TIME_INDEX 2

#define LEADERBOARD_PALETTE_HEADER_INDEX 0
#define LEADERBOARD_PALETTE_LEADERBOARD_INDEX 1
#define LEADERBOARD_PALETTE_YOUR_RANK_INDEX 2

typedef struct Leaderboard Leaderboard;

Object* Leaderboard_new(AEGfxTexture* font, AEVec2 pos, AEVec2 posDiff, AEVec2 charScale,
	Color palatte[LEADERBOARD_PALETTE_ROWS][LEADERBOARD_PALETTE_COLUMNS], 
	int yourRank, int ranksToDisplay, float addRankTime, unsigned camNum);

void Default_Leaderboard(unsigned camNum);
