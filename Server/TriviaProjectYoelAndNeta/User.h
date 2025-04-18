#pragma once
#include <string>

class User
{
public:
	User(const int& id, const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber);
    // Existing getters
    const std::string& getName() const;
    const std::string& getPassword() const;
    const std::string& getEmail() const;
    int getId() const;

    // Existing setters
    void setName(const std::string& name);
    void setPassword(const std::string& password);
    void setEmail(const std::string& email);
    void setId(const int& id);

    // New getters
    const std::string& getAddress() const;
    const std::string& getPhoneNumber() const;
    const std::string& getBirthDate() const;

    // New setters
    void setAddress(const std::string& address);
    void setPhoneNumber(const std::string& phoneNumber);
    void setBirthDate(const std::string& birthDate);

private:
    std::string _userName;
    std::string _password;
    std::string _email;
    std::string _address;
    std::string _phoneNumber;
    std::string _birthDate;
    int _id;
};