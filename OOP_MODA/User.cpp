#include "User.h"

User::User(): name(""), EGN(0), password(""), isLoggedIn(0) {}

User::User(const MyString& name, const MyString& password, const MyString& EGN): name(name), password(password), EGN(EGN) {}

MyString User::getName() const
{
    return name;
}

bool User::getLoggedInStatus() const
{
    return isLoggedIn;
}

void User::logout()
{
    isLoggedIn = false;
    std::cout << "You are successfully logged out.";
}

bool User::hasPermission(const MyString& action) const
{
    return action == "view_profile" ||
        action == "help" ||
        action == "logout";
}


