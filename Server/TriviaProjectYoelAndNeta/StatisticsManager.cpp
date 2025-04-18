#include "StatisticsManager.h"

std::vector<HighestScore> StatisticsManager::getHighScore()
{
	return m_database->getHighScores(NUM_OF_SCORES);
}

userStats StatisticsManager::getUserStatistics(int user_id)
{
	userStats user_stats;
	user_stats.user_id = user_id;
	user_stats.avg_ans_time = m_database->getPlayersAverageAnswerTime(user_id);
	user_stats.games_played = m_database->getNumOfPlayerGames(user_id);
	user_stats.highScore = m_database->getPlayerScore(user_id);
	user_stats.right_ans = m_database->getNumOfCorrectAnswers(user_id);
	user_stats.total_ans = m_database->getNumOfTotalAnswers(user_id);
	return user_stats;
}
