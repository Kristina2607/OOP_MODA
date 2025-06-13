#include "User.h"

User::User(Role role): name(""), EGN(0), password(""), isLoggedIn(0), role(role) {}

User::User(const MyString& name, const MyString& password, const MyString& EGN, Role role) : role(role), name(name), password(password), EGN(EGN), isLoggedIn(false) {}

MyString User::getName() const
{
    return name;
}

bool User::getLoggedInStatus() const
{
    return isLoggedIn;
}

bool User::checkPassword(const MyString& password) const
{
    return this->password == password;
}

bool User::checkLogData(const MyString& name, const MyString& password)
{
    return this->name == name && checkPassword(password);
}

void User::logout()
{
    isLoggedIn = false;
    std::cout << "You are successfully logged out.";
}

Role User::getRole() const
{
    return role;
}




