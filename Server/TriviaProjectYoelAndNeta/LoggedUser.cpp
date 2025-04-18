#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username;
}

std::string LoggedUser::getUsername() const
{
	return this->m_username;
}

int LoggedUser::getId() const
{
	return user_id;
}

bool LoggedUser::operator==(const LoggedUser& other)
{
	return other.getUsername() == this->m_username;
}
