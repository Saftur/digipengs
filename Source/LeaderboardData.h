/**
 * @file LeaderboardData.h
 * @author Parker Friedland
 * @date 1/24/2019
 * @brief Leaderboard
 */

#pragma once

#include "Leaderboard.h"

#define LEADERBOARD_SIZE 10
#define LEADERBOARD_NAME_LENGTH 15;

/**
* @brief data structure used to store leaderboard ranks. Stores the player name and their score associated with a given rank.
*/
typedef struct LeaderboardRank {
	unsigned long name_bytes_0_to_7;
	unsigned long name_bytes_8_to_15;
	float time;
	int minutes;
	int seconds;
} LeaderboardRank;

/**
* @brief retrieves leaderboard data. Should be called when the game starts or on load during the end screen level
*/
void Leaderboard_read();

/**
* @brief saves leaderboard data. Should be called when the game ends or on unload during the end screen level
*/
void Leaderboard_write();

void Leaderboard_getName(LeaderboardRank* rank, char* name);

void Leaderboard_setName(LeaderboardRank* rank, char* name);

/**
* @brief gets the player name and score data associated with a given name;
*/
LeaderboardRank* Leaderboard_getEntry(int rank);

/**
* @brief adds a new score to the leaderboard. If the leaderboard is full, it will only add the score if it is >= one of the scores already on the leaderboard.
*/
int Leaderboard_addEntry(const char* name, float time, int minutes, int seconds);

void Leaderboard_clear();