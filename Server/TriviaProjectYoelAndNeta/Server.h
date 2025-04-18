#pragma once
#include "pch.h"
#include <mutex>
#include <condition_variable>
#include "WSAInitializer.h"
#include "Server.h"
#include <deque>
#include <map>
#include "RequestHandlerFactory.h"


#define PORT 8826
class RequestHandlerFactory;

class Server
{
public:
	static Server& getInstance(IDatabase* db)
	{
		static Server instance(db);
		return instance;
	}

	// Delete copy constructor and assignment operator for singleton
	Server(Server const&) = delete;
	void operator=(Server const&) = delete;

	Server(IDatabase* db);
	~Server();
	void serve(int port);
	void run();
	void clear();

private:
	std::map<std::string, SOCKET> _users;
	std::deque<std::string> _listOfMessages;
	SOCKET _serverSocket;
	std::mutex _usersMu;
	std::mutex _messagesMu;
	std::map<std::string, std::mutex> _filesMutex;
	std::condition_variable _condForSendingMessage;	
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
};

