#pragma once
#include <string>
#include <vector>

class Question
{
public:
	Question(const std::string& question, const std::vector<std::string>& possibeleAnsowers, const std::string& correctAnsower);
	Question();
	std::string getQuestion() const;
	std::vector <std::string> getPossibleAnswers() const;
	std::string getCorrectAnswer() const;
	int getId() const;

	void setQuestion(const std::string& val);
	void setPossibleAnswers(const std::vector<std::string>& val);
	void setCorrectAnswer(const std::string& val);
	void setId(const int& val);
	void insertOptional(const std::string& val);

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	std::string m_correctAnswer;
	int m_id;
};