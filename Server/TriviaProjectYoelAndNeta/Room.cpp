#include "Room.h"

void Room::addUser(LoggedUser logged_user)
{	
	m_users.push_back(logged_user);
}

void Room::removeUser(LoggedUser logged_user)
{
	std::vector<LoggedUser>::iterator it;
	for (it = m_users.begin(); it != m_users.end(); ++it)
	{
		if ((*it).getUsername() == logged_user.getUsername()) // Find username with name to delete
		{
			m_users.erase(it);
		}
	}
}

// Create vector of all the connected users' usernames
std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> all_users; // Result vector
	std::vector<LoggedUser>::iterator it;
	for (it = m_users.begin(); it != m_users.end(); ++it)
	{
		all_users.push_back((*it).getUsername());
	}
	return all_users;
}

RoomData& Room::getRoomData()
{
	return m_metadata;
}
