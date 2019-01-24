
#include "stdafx.h"
#include "Leaderboard.h"
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
		if (entry.score >= Leaderboard_getEntry(i).score)
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