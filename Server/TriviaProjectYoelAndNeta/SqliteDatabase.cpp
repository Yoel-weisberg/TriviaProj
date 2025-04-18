#include "SqliteDatabase.h"
#include "json.hpp"

using json = nlohmann::json;


std::vector<User> SQLiteDatabase::users;
std::list<Question>  SQLiteDatabase::questions;
std::vector<HighestScore> SQLiteDatabase::highestScores;

SQLiteDatabase::SQLiteDatabase() :
	IDatabase()
{
	this->open();
}

bool SQLiteDatabase::open()
{
	sqlite3* db;
	int rc = sqlite3_open(DB, &db);
	if (rc) {
		return false;
	}
	this->_db = db;
	// Create Tables
	this->runCommand(CREATE_USERS_TABLE);
	this->runCommand(CREATE_QUISTIONS_TABLE);
	this->runCommand(CREATE_STATISTICS_TABLE);
	this->runCommand(CREATE_HIGHEST_SCORES_TABLE);
	return true;
}

bool SQLiteDatabase::close()
{
	return true;
}

bool SQLiteDatabase::doesUserExist(const std::string& userName)
{
	std::string query = "SELECT COUNT(*) FROM Users WHERE NAME = \"" + userName + "\";";
	int times = 0;
	this->runCommand(query, countCallback, &times);

	return times > 0;
}
bool SQLiteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	std::string userPassword; 
	std::string query = "SELECT PASSWORD FROM USERS WHERE NAME = '" + username + "';";
	runCommand(query, callbackUserPassword, &userPassword);
	return userPassword == password;
}

bool SQLiteDatabase::addNewUser(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber)
{
	std::string query = "INSERT INTO Users (NAME, PASSWORD, EMAIL, ADDRESS, PHONE_NUMBER, BIRTH_DATE) VALUES(\"" + name + "\", \"" + password + "\", \"" + email + "\", \"" + address + "\", \"" +  phoneNumber + "\", \"" + bitrthDate + "\");";
	this->runCommand(query);
	return true;
}

std::list<Question> SQLiteDatabase::getQuestions(const int& amount)
{
	std::string query = "SELECT * FROM t_questions LIMIT " + std::to_string(amount) + " ;";
	this->runCommand(query, loadIntoQuestions);
	return SQLiteDatabase::questions;
}

void SQLiteDatabase::loadQuestionsIntoDB()
{
	HINTERNET hInternet = InternetOpenA("HTTPGET", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternet) {
		std::cerr << "Failed to open internet handle" << std::endl;
		return;
	}

	HINTERNET hConnect = InternetOpenUrlA(hInternet, "https://opentdb.com/api.php?amount=10&difficulty=medium&type=multiple", NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (!hConnect) {
		std::cerr << "Failed to open URL" << std::endl;
		InternetCloseHandle(hInternet);
		return;
	}

	char buf[1024];
	DWORD bytesRead;
	std::string response;

	while (InternetReadFile(hConnect, buf, sizeof(buf), &bytesRead) && bytesRead > 0) {
		response.append(buf, bytesRead);
	}

	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);

	// turning string into json
	json jsonObject = json::parse(response);
	jsonObject = jsonObject["results"];
	for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it)
	{
		std::vector<std::string> incorrectAnswers;
		for (auto it : it.value()["incorrect_answers"])
		{
			incorrectAnswers.push_back(it);
		}
		Question question(it.value()["question"], incorrectAnswers, it.value()["correct_answer"]);
		this->insertQuestionIntoDB(question);
	}
}

void SQLiteDatabase::insertQuestionIntoDB(Question question)
{
	std::string sql = "INSERT INTO t_questions (question, correct_ans, ans2, ans3, ans4) VALUES (\"";
	sql += question.getQuestion();
	sql += "\", \"";
	sql += question.getCorrectAnswer();
	sql += "\", \"";
	sql += question.getPossibleAnswers()[0];
	sql += "\", \"";
	sql += question.getPossibleAnswers()[1];
	sql += "\", \"";
	sql += question.getPossibleAnswers()[2];
	sql += "\");";

	this->runCommand(sql);
}

int SQLiteDatabase::getTotalAmountOfQuestions()
{
	std::string query = "SELECT * FROM t_questions;";
	this->runCommand(query, loadIntoQuestions);
	return SQLiteDatabase::questions.size();
}

float SQLiteDatabase::getPlayersAverageAnswerTime(int user_id)
{
	float averageAnsTime;
	std::string query = "SELECT AVERAGE_ANS_TIME FROM Statistics WHERE ID = " + std::to_string(user_id) + " ;";
	this->runCommand(query, floatCallBack,&averageAnsTime);
	return averageAnsTime;
}

int SQLiteDatabase::getNumOfCorrectAnswers(int user_id)
{
	int numOfCorrectAns;
	std::string query = "SELECT CORRECT_ANS FROM Statistics WHERE ID = " + std::to_string(user_id) + " ;";
	this->runCommand(query, integerCallBack, &numOfCorrectAns);
	return numOfCorrectAns;
}

int SQLiteDatabase::getNumOfTotalAnswers(int user_id)
{
	int numOfTotalAns;
	std::string query = "SELECT TOTAL_ANS FROM Statistics WHERE ID = " + std::to_string(user_id) + " ;";
	this->runCommand(query, integerCallBack, &numOfTotalAns);
	return numOfTotalAns;
}

int SQLiteDatabase::getNumOfPlayerGames(int user_id)
{
	int numOfGamesPlayed;
	std::string query = "SELECT GAMES_PLAYED FROM Statistics WHERE ID = " + std::to_string(user_id) + " ;";
	this->runCommand(query, integerCallBack, &numOfGamesPlayed);
	return numOfGamesPlayed;
}

int SQLiteDatabase::getPlayerScore(int user_id)
{
	int playersScore;
	std::string query = "SELECT HIGHEST_SCORE FROM HIGHEST_SCORES WHERE ID = " + std::to_string(user_id) + " ;";
	this->runCommand(query, integerCallBack, &playersScore);
	return playersScore;
}

std::vector<HighestScore> SQLiteDatabase::getHighScores(int num_of_highScores)
{
	std::vector<HighestScore> highestScores;
	std::string query = "SELECT ID, HIGHEST_SCORE FROM HIGHEST_SCORES ORDER BY HIGHEST_SCORE DESC LIMIT " + std::to_string(num_of_highScores) + " ;";
	this->runCommand(query, loadIntoHighestScores);
	return SQLiteDatabase::highestScores;
}



bool SQLiteDatabase::runCommand(const std::string& sqlStatement, int(*callback)(void*, int, char**, char**), void* secondParam)
{
	SQLiteDatabase::users.clear();
	SQLiteDatabase::questions.clear();
	char** errMessage = nullptr;
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callback, secondParam, errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "error code: " << res;
		return false;
	}
	return true;
}

bool SQLiteDatabase::comparePasswords(const std::string& onePassword, const std::string& secondPassword)
{
	if (onePassword.length() != secondPassword.length())
	{
		return false;
	}
	for (int i = 0; i < onePassword.length(); i++)
	{
		if (onePassword[i] != secondPassword[i])
		{
			return false;
		}
	}
	return true;
}

int loadIntoUsers(void* data, int argc, char** argv, char** azColName)
{
	User user(0, "", "", "", "", "", "");

	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == NAME) {
			user.setName(argv[i]);
		}
		else if (std::string(azColName[i]) == ID) {
			user.setId(std::stoi(argv[i]));
		}
		else if (std::string(azColName[i]) == EMAIL) {
			user.setEmail(argv[i]);
		}
		else if (std::string(azColName[i]) == PASSWORD) {
			user.setPassword(argv[i]);
		}
	}
	SQLiteDatabase::users.push_back(user);
	return 0;
}

/**
 * countCallback - Callback function to count results.
 * Params: data - Data pointer, argc - Number of columns, argv - Array of column values,
 *         azColName - Array of column names
 * Returns: 0 to indicate success.
 */
int countCallback(void* data, int argc, char** argv, char** azColName)
{
	int* count = static_cast<int*>(data);
	if (argv[0]) {
		*count = std::stoi(argv[0]);
	}
	return 0;
}

int callbackUserPassword(void* _data, int argc, char** argv, char** azColName)
{
	auto& password = *static_cast<std::string*>(_data);

	if (std::string(azColName[0]) == PASSWORD)
		password = argv[0];

	return 0;
}

int loadIntoQuestions(void* _data, int argc, char** argv, char** azColName)
{
	Question question = Question();
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == QUESTION) {
			question.setQuestion(argv[i]);
		}
		else if (std::string(azColName[i]) == QUESTION_ID) {
			question.setId(std::stoi(argv[i]));
		}
		else if (std::string(azColName[i]) == CORRECT_ANS) {
			question.setCorrectAnswer(argv[i]);
		}
		else if (std::string(azColName[i]) == ANS_2 || std::string(azColName[i]) == ANS_3 || std::string(azColName[i]) == ANS_4) {
			question.insertOptional(argv[i]);
		}
	}
	SQLiteDatabase::questions.push_back(question);
	return 0;
}

int floatCallBack(void* _data, int argc, char** argv, char** azColName)
{
	auto& averageAnsTime = *static_cast<float*>(_data);
	if (argc == 1 && argv[0] != nullptr)
	{
		averageAnsTime == std::atoi(argv[0]);
		return 0;
	}
	return 1;
}

int integerCallBack(void* _data, int argc, char** argv, char** azColName)
{
	auto& averageAnsTime = *static_cast<int*>(_data);
	if (argc == 1 && argv[0] != nullptr)
	{
		averageAnsTime == std::atof(argv[0]);
		return 0;
	}
	return 1;
}

int loadIntoHighestScores(void* _data, int argc, char** argv, char** azColName)
{
	HighestScore highScore;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == ID)
		{
			highScore.user_id = std::stoi(argv[i]);
		}
		else if (std::string(azColName[i]) == NAME)
		{
			highScore.username = argv[i];
		}
		else if (std::string(azColName[i]) == HIGHEST_SCORE)
		{
			highScore.newHighScore = std::stof(argv[i]);
		}
	}
	SQLiteDatabase::highestScores.push_back(highScore);
	return 0;
}

