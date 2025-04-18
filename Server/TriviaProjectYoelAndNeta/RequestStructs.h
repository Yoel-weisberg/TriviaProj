#pragma once
#include <string>
#include <vector>
#include <chrono>
class IRequestHandler; // Forward declaration


typedef struct LoginRequest
{
	std::string userName;
	std::string password;
};


typedef struct SignUpRequest
{
	std::string userName;
	std::string password;
	std::string email;
	std::string address;
	std::string phoneNumber;
	std::string birthDate;
};

typedef struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
};

typedef struct RequestInfo
{
	int RequestId;
	std::time_t receivalTime;
	std::vector<unsigned char> buffer;
};

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

typedef struct JoinRoomRequest
{
	unsigned int roomId;
};

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};