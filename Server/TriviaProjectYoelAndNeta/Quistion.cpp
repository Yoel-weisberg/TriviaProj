#include "Quistion.h"

Question::Question(const std::string& question, const std::vector<std::string>& possibleAnsowers, const std::string& correctAnsower) :
    m_correctAnswer(correctAnsower), m_possibleAnswers(possibleAnsowers), m_question(question)
{
}

Question::Question()
{
}

std::string Question::getQuestion() const
{
    return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
    return this->m_possibleAnswers;
}

std::string Question::getCorrectAnswer() const
{
    return this->m_correctAnswer;
}

int Question::getId() const
{
    return this->m_id;
}

void Question::setQuestion(const std::string& val)
{
    this->m_question = val;
}

void Question::setPossibleAnswers(const std::vector<std::string>& val)
{
    this->m_possibleAnswers = val;
}

void Question::setCorrectAnswer(const std::string& val)
{
    this->m_correctAnswer = val;
}

void Question::setId(const int& val)
{
    this->m_id = val;
}

void Question::insertOptional(const std::string& val)
{
    this->insertOptional(val);
}
