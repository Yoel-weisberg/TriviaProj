#include "Server.h"
#include "pch.h"
#include "Helper.h"
#include "Communicator.h"

#define LENGTH 1024
#define CODE_LENGTH 3
#define FIRST_DIGIT 3
#define LENGTH_OF_LENGTH_OF_NAME 2
#define LENGTH_OF_LENGTH_OF_MESSEGE 5
#define NAME_INDEX 5
#define REG_UPDATE "Just update"
#define EXIT "EXIT"

/**
 * Constructor for Server class.
 * Initializes a TCP server socket. If socket creation fails, throws an exception.
 */
Server::Server(IDatabase* db) : m_database(db), m_handlerFactory(db)
{
	// Create a TCP server socket
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// Check for socket creation failure
	if (_serverSocket == INVALID_SOCKET)
	{
		std::cout << "Error: " << WSAGetLastError() << std::endl;
		closesocket(_serverSocket);
		std::cerr << "Closed socket since an error occoured " << std::endl;
		throw std::exception(__FUNCTION__ " - socket");
	}
}

/**
 * Destructor for Server class.
 * Closes the server socket if it is valid.
 */
Server::~Server()
{
	try
	{
		// Close the server socket
		closesocket(_serverSocket);
	}
	catch (...) {}
}

/**
 * Starts the server to listen on a specified port.
 * Binds the server socket to the given port and starts listening for incoming connections.
 *
 * @param port The port number on which the server will listen.
 */
void Server::serve(int port)
{
	struct sockaddr_in sa = { 0 };

	// Set up the sockaddr_in structure
	sa.sin_port = htons(port); // Set the port to listen on
	sa.sin_family = AF_INET;   // Use IPv4 addresses
	sa.sin_addr.s_addr = INADDR_ANY;    // Listen on all available interfaces

	// Bind the server socket to the specified port
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming connections
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;
}

void Server::run()
{
	try
	{
		this->serve(PORT);
		RequestHandlerFactory& handler = RequestHandlerFactory::getInstance(this->m_database);
		Communicator& myCommunicator = Communicator::getInstance(this->_serverSocket, handler);
		std::thread t_connector(&Communicator::startHandleRequests, &myCommunicator);

		t_connector.detach();
		
		std::string input = "";
		while (input != EXIT)
		{
			std::cout << "Enter something" << std::endl;
			std::cin >> input;
		}
		this->clear();
		exit(1);
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
}

void Server::clear()
{
	closesocket(this->_serverSocket);
}
