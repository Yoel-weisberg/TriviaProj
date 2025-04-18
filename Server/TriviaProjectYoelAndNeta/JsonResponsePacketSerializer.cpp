#include "JsonResponsePacketSerializer.h" // Including the header file JsonResponsePacketSerializer.h

#define MESSEGE_SIZE_TO_SIZE 5 // Defining a constant MESSEGE_SIZE_TO_SIZE with value 5
#define BYTE 8 // Defining a constant BYTE with value 8
#define CODE_LENGTH 1 // Defining a constant CODE_LENGTH with value 1
#define MESSEGE_LENGTH_LENGTH 4 // Defining a constant MESSEGE_LENGTH_LENGTH with value 4

// Function to serialize login response into a vector of unsigned char
std::vector<unsigned char> JsonResponsePacketSerialize::serializeLoginResponse(const LoginResponse& response)
{
    json j = json{ {"status", response.status} }; // Creating a JSON object j with the status field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, CODE_LOGIN_RESP); // Parsing the data into a message with the specified response code
}


// Function to serialize sign up response into a vector of unsigned char
std::vector<unsigned char> JsonResponsePacketSerialize::serializeSignUpResponse(const SignupResponse& response)
{
    json j = json{ {"status", response.status} }; // Creating a JSON object j with the status field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, CODE_SIGN_UP_RESP); // Parsing the data into a message with the specified response code
}

// Function to serialize error response into a vector of unsigned char
std::vector<unsigned char> JsonResponsePacketSerialize::serializeErrorResponse(const ErrorResponse& response)
{
    json j = json{ {"message", response.message} }; // Creating a JSON object j with the message field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, CODE_ERROR_RESPONSE); // Parsing the data into a message with the specified response code
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeLogoutResponse(const LogoutResponse& response)
{
    json j = json{ {"status", response.status} }; // Creating a JSON object j with the message field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, LOGOUT_RESP); // Parsing the data into a message with the specified response code
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeGetRoomResponse(const GetRoomsResponse& response)
{
    std::string roomsString = "[ ";
    for (auto it = response.rooms.begin(); it != response.rooms.begin(); ++it)
    {
        roomsString += "id: " + std::to_string(it->id) + ", ";
        roomsString += "name: " + it->name + ", ";
        roomsString += "maxPlayers: " + std::to_string(it->maxPlayers) + ", ";
        roomsString += "numOfQuestionsInGame: " + std::to_string(it->numOfQuestionsInGame);
        roomsString += "timePerQuestion: " + std::to_string(it->timePerQuestion) + ", ";
        roomsString += "isActive: " + std::to_string(it->isActive) + "]";
    }
    json j = json{ {"rooms", roomsString}, {"status", response.status}}; // Creating a JSON object j with the message field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, GET_ROOM_RESP); // Parsing the data into a message with the specified response code
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& response)
{
    std::string playersString = "[ ";
    for (auto it = response.players.begin(); it != response.players.end(); it++)
    {
        playersString += *it;
    }
    json j = json{ {"players", playersString} };
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, GET_PLAYERS_RESP); // Parsing the data into a message with the specified response code
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeJoinRoomResponse(const JoinRoomResponse& response)
{
    json j = json{ {"status", response.status} }; // Creating a JSON object j with the message field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, JOIN_ROOM_RESP); // Parsing the data into a message with the specified response code
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeCreateRoomResponse(const CreateRoomResponse& response)
{
    json j = json{ {"status", response.status} }; // Creating a JSON object j with the message field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, CREATE_ROOM_RESP); // Parsing the data into a message with the specified response code
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeHighScoreResponse(const GetHighScoreResponse& response)
{
    json stats = {};
    for (const auto& it : response.statistics)
    {
        json innerJson = {
            {USERNAME, it.username},
            {HIGH_SCORE, it.newHighScore}
        };
        stats.push_back(innerJson);
    }
    json j = json{ {"statistics", stats}, {"status", response.status}}; // Creating a JSON object j with the message field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, GET_HIGH_SCORE_RESP); // Parsing the data into a message with the specified response code
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeGetPersonalStatsResponse(const GetPersonalStatsResponse& response)
{
    json statsJson = { {"user_id", response.statistics.user_id}, {"total_ans", response.statistics.total_ans}, {"avg_ans_time", response.statistics.avg_ans_time }, {"games_played", response.statistics.games_played}, {"highScore", response.statistics.highScore}, {"right_ans", response.statistics.right_ans} };
    json j = json{ {"statistics", statsJson}, {"status", response.status}}; // Creating a JSON object j with the message field from the response
    return JsonResponsePacketSerialize::parseDataIntoMessage(j, GET_PERSONAL_STATS_RESP); // Parsing the data into a message with the specified response code
}



// Function to parse data into a message
std::vector<unsigned char> JsonResponsePacketSerialize::parseDataIntoMessage(json j, const int& respCode)
{

    std::string json_str = j.dump(); // Converting the JSON object to a string
    // Convert string to bytes
    std::vector<unsigned char> bytes(json_str.begin(), json_str.end()); // Creating a vector of unsigned char containing the bytes of the JSON string


    std::vector<unsigned char> res; // Creating a vector of unsigned char to hold the resulting message

    // putting the code inside
    std::vector<unsigned char> code = JsonResponsePacketSerialize::turnIntToBytes(respCode); // Converting the response code to bytes
    for (int i = 0; i < code.size() + 1; i++) // Looping through the bytes of the response code
    {
        code.pop_back(); // Removing the last byte
    }
    res.insert(res.end(), code.begin(), code.end()); // Inserting the bytes of the response code into the result

    // getting message size 
    std::vector<unsigned char> sizeOfMessage = JsonResponsePacketSerialize::turnIntToBytes(bytes.size()); // Converting the size of the data to bytes
    res.insert(res.end(), sizeOfMessage.begin(), sizeOfMessage.end()); // Inserting the bytes of the message size into the result

    // putting in the message data
    res.insert(res.end(), bytes.begin(), bytes.end()); // Inserting the bytes of the message data into the result

    return res; // Returning the resulting message
}

// Function to convert an integer to bytes
std::vector<unsigned char> JsonResponsePacketSerialize::turnIntToBytes(const int& num)
{
    std::vector<unsigned char> bytes(sizeof(int)); // Creating a vector of unsigned char to hold the bytes of the integer

    for (size_t i = 0; i < sizeof(int); ++i) { // Looping through each byte of the integer
        bytes[i] = static_cast<unsigned char>((num >> (i * 8)) & 0xFF); // Extracting the byte and storing it in the vector
    }

    return bytes; // Returning the vector of bytes
}

// Function to pad a vector with zeros
void JsonResponsePacketSerialize::padWithZeros(std::vector<unsigned char>* data, const int& amountOfZero)
{
    while (data->size() <= amountOfZero) // Looping until the size of the vector is greater than the amount of zeros needed
    {
        data->insert(data->begin(), 0); // Inserting a zero at the beginning of the vector
    }
}
