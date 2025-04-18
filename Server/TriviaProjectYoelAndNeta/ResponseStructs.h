#pragma once
#include "RoomData.h"
#include <vector>
#include "StatisticsManager.h"
#include "HighestScore.h"
typedef struct LoginResponse
{
	unsigned int status;
};

typedef struct SignupResponse
{
	unsigned int status;
};

typedef struct ErrorResponse
{
	std::string message;
};
typedef struct LogoutResponse
{
	unsigned int status;
};

typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

typedef struct GetPlayersInRoomResponse
{
	unsigned int status;
	std::vector<std::string> players;
};

typedef struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<HighestScore> statistics;
};


typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	userStats statistics;
};

typedef struct JoinRoomResponse
{
	unsigned int status;
};

typedef struct CreateRoomResponse
{
	unsigned int status;
};