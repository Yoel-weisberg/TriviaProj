#include "User.h"
User::User(const int& id,const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber) :
    _id(id), _userName(name), _password(password), _email(email), _address(address), _birthDate(bitrthDate), _phoneNumber(phoneNumber)
{
}

// Getter implementations
const std::string& User::getName() const {
    return _userName;
}

const std::string& User::getPassword() const {
    return _password;
}

const std::string& User::getEmail() const {
    return _email;
}

int User::getId() const
{
    return this->_id;
}

// Setter implementations
void User::setName(const std::string& name) {
    _userName = name;
}

void User::setPassword(const std::string& password) {
    _password = password;
}

void User::setEmail(const std::string& email) {
    _email = email;
}

void User::setId(const int& id)
{
    this->_id = id;
}

const std::string& User::getAddress() const {
    return _address;
}

const std::string& User::getPhoneNumber() const {
    return _phoneNumber;
}

const std::string& User::getBirthDate() const {
    return _birthDate;
}

// Implementations of new setters
void User::setAddress(const std::string& address) {
    _address = address;
}

void User::setPhoneNumber(const std::string& phoneNumber) {
    _phoneNumber = phoneNumber;
}

void User::setBirthDate(const std::string& birthDate) {
    _birthDate = birthDate;
}
