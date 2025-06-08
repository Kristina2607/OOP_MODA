#pragma once
#include "MyString.h"

class Client;
class Business;
class Administrator;

class LoggedUser
{
private:
	User* user;

public:
	bool checkPassword(const MyString& input) const;
};

