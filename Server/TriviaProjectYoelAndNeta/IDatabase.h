#pragma once
#include <iostream>
#include "Quistion.h"
#include "HighestScore.h"
#include <list>
class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;
	virtual bool addNewUser(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber) = 0;

	// ---- Questions related ----
	virtual std::list<Question> getQuestions(const int& amount) = 0;
	virtual void loadQuestionsIntoDB() = 0;
	virtual void insertQuestionIntoDB(Question question) = 0;
	virtual int getTotalAmountOfQuestions() = 0;
	// ---- Statistics related ----
	virtual float getPlayersAverageAnswerTime(int user_id) = 0;
	virtual int getNumOfCorrectAnswers(int user_id) = 0;
	virtual int getNumOfTotalAnswers(int user_id) = 0;
	virtual int getNumOfPlayerGames(int user_id) = 0; // Return the number of games a player has played
	virtual int getPlayerScore(int user_id) = 0;
	virtual std::vector<HighestScore> getHighScores(int num_of_highScores) = 0; // Return 5 highest scores
	
};
