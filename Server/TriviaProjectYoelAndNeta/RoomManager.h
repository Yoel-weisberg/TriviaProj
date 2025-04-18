#pragma once
#include <map>
#include "Room.h"

class RoomManager
{
public:


	//static RoomManager& getInstance()
	//{
	//	static RoomManager instance;
	//	return instance;
	//}

	//// Delete copy constructor and assignment operator for singleton
	//RoomManager(RoomManager const&) = delete;
	//void operator=(RoomManager const&) = delete;

	RoomManager();

	void createRoom(LoggedUser logged_user, RoomData room_data);
	void DeleteRoom(int room_id);
	unsigned int getRoomState(int room_id); // Return the 'isActive' variable of the room
	bool doesRoomExist(int room_id);

	// ---- Getters ----
	std::vector<RoomData> getRooms();
	Room& getRoom(int room_id);

private:
	std::map<int, Room> m_rooms; // Map for the room and its' id
};
