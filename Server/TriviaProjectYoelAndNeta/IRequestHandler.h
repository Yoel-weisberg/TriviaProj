#pragma once
#include "pch.h"

struct RequestInfo; // Forward declaration
struct RequestResult; // Forward declaration

class IRequestHandler
{
public: 
	virtual bool isRequestRelevant(RequestInfo& reqInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo& reqInfo) = 0;
};