#pragma once
#include <string>
#include <iostream>
#include <regex>
 
class UserCheckers
{
public:
	static bool checkPassword(const std::string& password);
	static bool checkEmail(const std::string& email);
	static bool checkAddress(const std::string& address);
	static bool checkPhone(const std::string& phoneNumber);
	static bool checkBirth(const std::string& birth);
};
