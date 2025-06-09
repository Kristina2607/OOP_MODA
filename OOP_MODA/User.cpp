#include "User.h"

User::User(): name(""), EGN(0), password(""), isLoggedIn(0), role(Role::Any) {}

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

void User::logout()
{
    isLoggedIn = false;
    std::cout << "You are successfully logged out.";
}

Role User::getRole() const
{
    return role;
}



