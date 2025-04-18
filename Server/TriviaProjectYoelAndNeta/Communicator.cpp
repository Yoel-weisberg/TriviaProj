#include "Communicator.h"
#define MESSEGE_LENGTH 1024
Communicator::Communicator(const SOCKET& socket, RequestHandlerFactory& handleFactory) : m_serverSocket(socket), m_handlerFactory(handleFactory)
{
}

void Communicator::startHandleRequests()
{
	while (true)
	{
		try
		{
			// Output message indicating waiting for client connections
			std::cout << "Waiting for client connection request" << std::endl;

			// Accept a new client connection
			SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
			if (client_socket == INVALID_SOCKET)
			{
				throw std::exception(__FUNCTION__);
			}

			// Output message indicating client acceptance
			std::cout << "Client accepted. Server and client can speak" << std::endl;

			m_clients[client_socket] = (IRequestHandler*) new LoginRequestHandler(m_handlerFactory.GetLoginManager(), m_handlerFactory);
			// Create a new thread to handle requests for this client
			std::thread userThread(&Communicator::handleNewClient, this, client_socket);
			userThread.detach(); // Detach the thread
		}
		catch (const std::exception&)
		{
			// Output error message
			std::cerr << "User erupted" << std::endl;
		}
	}
}

void Communicator::sendData(const SOCKET sc, std::vector<unsigned char>& message, const int& flags)
{
	if (send(sc, this->unsignedToChar(message), message.size() * sizeof(unsigned char), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}

}

std::vector<unsigned char> Communicator::getDataFromSocket(const SOCKET sc, const int bytesNum, const int& flags)
{

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::vector<unsigned char> received = this->charToUnsigned(data, bytesNum);
	delete[] data;
	return received;
}

void Communicator::handleNewClient(const SOCKET& userSocket)
{
	//Inserting user into the map
   /*LoginRequestHandler* newHandler = new LoginRequestHandler(m_handlerFactory);
   this->m_usersMu.lock();
   this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(userSocket, newHandler));
   this->m_usersMu.unlock();*/
	while (true)
	{
		try
		{
			std::vector<unsigned char> clientMessage = this->getDataFromSocket(userSocket, MESSEGE_LENGTH);
			if (clientMessage[0] == MT_CLIENT_EXIT) // Check if user wants to log out
			{
				if (std::string(clientMessage.begin(), clientMessage.end()) == "logout")
				{
					RequestInfo logout_req = { static_cast<RequestCodes>(LOGOUT_REQ), getCurrentTime(), clientMessage };
					RequestResult res = m_clients.find(userSocket)->second->handleRequest(logout_req);
				}
				closesocket(userSocket);
				m_clients.erase(userSocket);
			}

			//RequestInfo reqInfo;
			//reqInfo.buffer = clientMessage;
			//reqInfo.receivalTime = getCurrentTime();
			//reqInfo.RequestId = clientMessage[0];
			RequestInfo reqInfo = { static_cast<RequestCodes>(clientMessage[0]), getCurrentTime(), clientMessage };
			if (m_clients.find(userSocket)->second != nullptr && m_clients.find(userSocket)->second->isRequestRelevant(reqInfo))
			{
				RequestResult resResult = m_clients.find(userSocket)->second->handleRequest(reqInfo);
				if (resResult.newHandler != nullptr) // Update handler if valid
				{
					m_clients.find(userSocket)->second = resResult.newHandler;
				}
				//std::string response_as_string = std::string(resResult.response.begin(), resResult.response.end());
				if (std::string(resResult.response.begin(), resResult.response.end()) != "")
				{
					sendData(userSocket, resResult.response);
				}
			}
			//if (newHandler->isRequestRelevant(reqInfo)) // For a valid request, move user to the next state
			//{
			//	RequestResult resp = newHandler->handleRequest(reqInfo);
			//	this->sendData(userSocket, resp.response);

			//}
			else // Assemble error response
			{
				ErrorResponse err;
				err.message = INVALID_REQUEST;
				std::vector<unsigned char> errorMessage = JsonResponsePacketSerialize::serializeErrorResponse(err);
				this->sendData(userSocket, errorMessage);
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			closesocket(userSocket);
		}
	}
}

std::vector<unsigned char> Communicator::charToUnsigned(const char* data, const int& length)
{
	std::vector<unsigned char> res;
	for (int i = 0; i < length; i++)
	{
		res.push_back(data[i]);
	}
	return res;
}

char* Communicator::unsignedToChar(const std::vector<unsigned char>& data)
{
	char* res = new char[data.size()];
	for (int i = 0; i < data.size(); i++)
	{
		res[i] = data[i];
	}
	return res;
}


time_t Communicator::getCurrentTime()
{
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	return end_time;
}

