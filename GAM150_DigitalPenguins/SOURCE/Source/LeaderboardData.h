/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file LeaderboardData.h
 * @author Parker Friedland
 * @date 1/24/2019
 * @brief Leaderboard
 */

#pragma once

#include "Leaderboard.h"

#define LEADERBOARD_SIZE 10

/**
* @brief data structure used to store leaderboard ranks. Stores the player name and their score associated with a given rank.
*/
typedef struct LeaderboardRank {
	char name[LEADERBOARD_NAME_LENGTH];
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

/**
* @brief gets the player name and score data associated with a given name;
*/
LeaderboardRank* Leaderboard_getEntry(int rank);

/**
* @brief adds a new score to the leaderboard. If the leaderboard is full, it will only add the score if it is >= one of the scores already on the leaderboard.
*/
int Leaderboard_addEntry(const char* name, float time, int minutes, int seconds);

void Leaderboard_clear();