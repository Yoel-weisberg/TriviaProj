#include "JsonRequestPacketDeserializer.h"
#define LENGTH_PART_END 5
#define JSON_START 6
#define SHIFT 5
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char> buffer)
{
	json json_data = JsonRequestPacketDeserializer::convertBuferToRequestParser(buffer);
	return LoginRequest({ json_data[USERNAME], json_data[PASSWORD]});
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const std::vector<unsigned char> buffer)
{
	json json_data = JsonRequestPacketDeserializer::convertBuferToRequestParser(buffer);
	return SignUpRequest({ json_data[USERNAME], json_data[PASSWORD], json_data[EMAIL], json_data[ADDRESS], json_data[PHONE_NUMBER], json_data[BIRTH_DATE]});
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const std::vector<unsigned char> buffer)
{
	json json_data = JsonRequestPacketDeserializer::convertBuferToRequestParser(buffer);
	return GetPlayersInRoomRequest({ json_data[ROOM_ID] });
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::vector<unsigned char> buffer)
{
	json json_data = JsonRequestPacketDeserializer::convertBuferToRequestParser(buffer);
	return JoinRoomRequest({ json_data[ROOM_ID] });
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<unsigned char> buffer)
{
	json json_data = JsonRequestPacketDeserializer::convertBuferToRequestParser(buffer);
	return CreateRoomRequest({ json_data[ROOM_NAME], json_data[MAX_USERS], json_data[QUESTION_COUNT], json_data[ANSOWER_TIMEOUT]});
}

int JsonRequestPacketDeserializer::convertUnsignedToInt(const std::vector<unsigned char>& buffer)
{
	// Convert bytes to integer
	int result = 0;
	for (size_t i = 0; i < buffer.size(); ++i) {
		result = (result << 8) | buffer[i];
	}
	return result;
}

json JsonRequestPacketDeserializer::convertBuferToRequestParser(const std::vector<unsigned char>& buffer)
{
	// Convert buffer to string
	std::vector <unsigned char> copyCharConsistingOfLength(buffer.begin() + 1, buffer.begin() + LENGTH_PART_END);
	int messageSize = JsonRequestPacketDeserializer::convertUnsignedToInt(copyCharConsistingOfLength);
	std::string data(buffer.begin() + LENGTH_PART_END, buffer.begin() + messageSize + SHIFT);
	
	// Extract Json part
	data = data.substr(data.find('{'));
	json json_data = json::parse(data); // Parse to json
	return json_data;
}
