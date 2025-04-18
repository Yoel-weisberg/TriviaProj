#pragma once
#include <vector>
#include <iostream>
#include "IDatabase.h"

#define NUM_OF_SCORES 3

struct userStats
{
	int user_id;
	int right_ans;
	int total_ans;
	float highScore;
	int avg_ans_time;
	int games_played;
};

class StatisticsManager
{
public:
	std::vector<HighestScore> getHighScore();
	userStats getUserStatistics(int user_id);
private:
	IDatabase* m_database;
};
