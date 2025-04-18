#pragma once

#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>
#include <iterator>

class Room
{
public:
	void addUser(LoggedUser logged_user);
	void removeUser(LoggedUser logged_user);
	std::vector<std::string> getAllUsers();
	RoomData& getRoomData();
private:
	RoomData m_metadata;
	std::vector<LoggedUser>	m_users;
};
