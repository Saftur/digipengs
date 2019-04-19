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

void Leaderboard_getName(LeaderboardRank* rank, char* name)
{
	memmove(name, &(rank->name_bytes_0_to_7), sizeof(unsigned long));
	memmove(name + 8, &(rank->name_bytes_8_to_15), sizeof(unsigned long));
}

void Leaderboard_setName(LeaderboardRank* rank, char* name)
{
	memmove(&(rank->name_bytes_0_to_7), name, sizeof(unsigned long));
	memmove(&(rank->name_bytes_8_to_15), name + 8, sizeof(unsigned long));
}

LeaderboardRank* Leaderboard_getEntry(int rank)
{
	if (0 <= rank-1 && rank-1 < LEADERBOARD_SIZE)
	{
		return &leaderboard[rank-1];
	}
	else
	{
		return NULL;
	}
}

int Leaderboard_addEntry(const char* name, float time, int minutes, int seconds)
{
	for (unsigned i = 0; i < LEADERBOARD_SIZE; i++) 
	{

		if (time <= leaderboard[i].time || leaderboard[i].time == 0)
		{
			memmove(leaderboard + i + 1, leaderboard + i, (LEADERBOARD_SIZE - i - 1) * sizeof(LeaderboardRank));
			Leaderboard_setName(leaderboard + i, name);
			leaderboard[i].time = time;
			leaderboard[i].minutes = minutes;
			leaderboard[i].seconds = seconds; 

			return i+1;
		}
	}

	return 0;
}

void Leaderboard_clear()
{
	memset(leaderboard, 0, sizeof(LeaderboardRank) * LEADERBOARD_SIZE);
}