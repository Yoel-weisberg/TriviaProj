#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class LoginManager;

class LoginRequestHandler : public IRequestHandler
{
public:
	static LoginRequestHandler& getInstance(LoginManager& loginManager, RequestHandlerFactory& handleFactory)
	{
		static LoginRequestHandler instance(loginManager, handleFactory);
		return instance;
	}

	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handleFactory);
	bool isRequestRelevant(RequestInfo& reqInfo) override;
	RequestResult handleRequest(RequestInfo& reqInfo) override;
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handleFactory;
};
