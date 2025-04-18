#pragma once

// ---- Response Codes ----
enum ResponseCodes
{
	CODE_LOGIN_RESP = 200,
	CODE_SIGN_UP_RESP,
	CODE_ERROR_RESPONSE,
	LOGOUT_RESP,
	GET_ROOM_RESP,
	GET_PLAYERS_RESP,
	JOIN_ROOM_RESP,
	CREATE_ROOM_RESP,
	GET_HIGH_SCORE_RESP,
	GET_PERSONAL_STATS_RESP
};

enum RequestCodes
{
	CODE_LOGIN_REQ = 100,
	CODE_SIGN_UP_REQ,
	CODE_ERROR_REQ,
	LOGOUT_REQ,
	GET_ROOM_REQ,
	GET_PLAYERS_REQ,
	JOIN_ROOM_REQ,
	CREATE_ROOM_REQ,
	GET_HIGH_SCORE_REQ,
	GET_PERSONAL_STATS_REQ
};

// ---- Message constants ----
#define USERNAME "username"
#define PASSWORD "password"
#define EMAIL "email"
#define ADDRESS "address"
#define PHONE_NUMBER "phone_number"
#define BIRTH_DATE "birth_date"


// ---- Error Messages ----
#define INVALID_REQUEST "Invalid Request"

#define ROOM_ID "roomId"

#define ROOM_NAME "roomName"
#define MAX_USERS "maxUsers"
#define QUESTION_COUNT "questionCount"
#define ANSOWER_TIMEOUT "answerTimeout"

// ---- Room Settings ----
#define MIN_ANS_TIME 1
#define MIN_USERS 1
#define MIN_NUM_OF_QUESTIONS 1
#define ACTIVE_ROOM 1
#define INACTIVE_ROOM 0 

// ---- Statistics Settings ----
#define HIGH_SCORE "highestScore"
