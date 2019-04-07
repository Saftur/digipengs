/**
 * @file LeaderboardData.c
 * @author Parker Friedland
 * @date 1/24/2019
 * @brief Leaderboard
 */

#include "stdafx.h"
#include "LeaderboardData.h"
#include <stdio.h>
#include <string.h>

static LeaderboardRank leaderboard[LEADERBOARD_SIZE] = { 0 };

void Leaderboard_read() 
{
	FILE *file;
	fopen_s(&file, "Leaderboard.bin", "rb");
	if (!file) 
	{
		memset(leaderboard, 0, sizeof(LeaderboardRank) * LEADERBOARD_SIZE);
		return;
	}
	fread(leaderboard, sizeof(LeaderboardRank), LEADERBOARD_SIZE, file);
	fclose(file);
}

void Leaderboard_write() 
{
	FILE *file;
	fopen_s(&file, "Leaderboard.bin", "wb");
	fwrite(leaderboard, sizeof(LeaderboardRank), LEADERBOARD_SIZE, file);
	fclose(file);
}

LeaderboardRank* Leaderboard_getEntry(unsigned rank)
{
	if (rank < LEADERBOARD_SIZE)
	{
		return &leaderboard[rank];
	}
	else
	{
		return NULL;
	}
}

int Leaderboard_addEntry(char* name, float time, int minutes, int seconds)
{
	for (unsigned i = 0; i < LEADERBOARD_SIZE; i++) 
	{

		if (time <= leaderboard[i].time || leaderboard[i].time == 0)
		{
			char *tempName = NULL, *nextName = name; 
			float tempTime = 0, nextTime = time;
			int tempMinutes = 0, nextMinuets = minutes;
			int tempSeconds = 0, nextSeconds = seconds;

			for (i; i < LEADERBOARD_SIZE; i++)
			{
				if (i != 0)
				{
					tempName = leaderboard[i].name;
					tempTime = leaderboard[i].time;
					tempMinutes = leaderboard[i].minutes;
					tempSeconds = leaderboard[i].seconds;
				}

				leaderboard[i].name = nextName;
				leaderboard[i].time = nextTime;
				leaderboard[i].minutes = nextMinuets;
				leaderboard[i].seconds = nextSeconds;

				nextName = tempName;
				nextTime = tempTime;
				nextMinuets = tempMinutes;
				nextSeconds = tempSeconds;
			}

			if (nextName != NULL)
			{
				free(nextName);
			}

			return i+1;
		}
	}

	return 0;
}