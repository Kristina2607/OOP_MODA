#pragma once
#include "User.h"
#include "HeterogeneousContainer.hpp"

class UserManager
{
	HeterogeneousContainer<User> users;

public:
	void registerUser();
	User* logout();
	~UserManager();
};

