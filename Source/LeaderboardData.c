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

LeaderboardRank Leaderboard_getEntry(unsigned rank)
{
	if (rank < LEADERBOARD_SIZE)
	{
		return leaderboard[rank];
	}
	else
	{
		return (LeaderboardRank){ 0 };
	}
}

void Leaderboard_addEntry(LeaderboardRank entry)
{
	for (unsigned i = 0; i < LEADERBOARD_SIZE; i++) 
	{
		if (entry.time <= Leaderboard_getEntry(i).time || Leaderboard_getEntry(i).time == 0)
		{
			LeaderboardRank temp, next = entry;

			for (i; i < LEADERBOARD_SIZE; i++)
			{
				temp = leaderboard[i];
				leaderboard[i] = next;
				next = temp;
			}
		}
	}
}