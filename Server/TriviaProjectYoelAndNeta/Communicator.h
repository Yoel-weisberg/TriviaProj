#pragma once
#include "IRequestHandler.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include "MenuRequestHandler.h"

class Communicator
{
public:
	static Communicator& getInstance(const SOCKET& socket, RequestHandlerFactory& handleFactory)
	{
		static Communicator instance(socket, handleFactory);
		return instance;
	}

	// Delete copy constructor and assignment operator for singleton
	Communicator(Communicator const&) = delete;
	void operator=(Communicator const&) = delete;

	Communicator(const SOCKET& socket, RequestHandlerFactory& handleFactory);
	void startHandleRequests();
	void sendData(const SOCKET sc, std::vector<unsigned char>& message, const int& flags = 0);
	std::vector<unsigned char> getDataFromSocket(const SOCKET sc, const int bytesNum, const int& flags = 0);
private:
	void handleNewClient(const SOCKET& userSocket);
	std::vector  <unsigned char> charToUnsigned(const char* data, const int& length );
	char* unsignedToChar(const std::vector<unsigned char>& data);
	time_t getCurrentTime();
	//int getMessageCode()

	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;
	std::mutex m_usersMu;	
	RequestHandlerFactory& m_handlerFactory;
};
