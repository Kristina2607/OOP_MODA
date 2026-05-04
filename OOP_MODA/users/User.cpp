#include "User.h"

User::User(Role role): name(""), EGN(0), password(""), isLoggedIn(0), role(role) {}

User::User(std::ifstream& ifs)
{
    deserialize(ifs);
}

User::User(const MyString& name, const MyString& password, const MyString& EGN, Role role) : role(role), name(name), password(password), EGN(EGN), isLoggedIn(false) {}

const MyString& User::getName() const
{
    return name;
}

const MyString& User::getEGN() const
{
    return EGN;
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

void User::serialize(std::ofstream& ofs) const
{
    int userRoleValue = (int)this->getRole();
    ofs.write((const char*)(&userRoleValue), sizeof(int));

    MyString::writeStringToFile(ofs, name);
    MyString::writeStringToFile(ofs, password);
    MyString::writeStringToFile(ofs, EGN);

    ofs.write((const char*)(&isLoggedIn), sizeof(bool));
}

void User::deserialize(std::ifstream& ifs) {
   
    int userRoleValue = 0;
    ifs.read((char*)(&userRoleValue), sizeof(int));
    Role userRole = static_cast<Role>(userRoleValue);

    name = MyString::readStringFromFile(ifs);
    password = MyString::readStringFromFile(ifs);
    EGN = MyString::readStringFromFile(ifs);

    ifs.read((char*)(&isLoggedIn), sizeof(bool));
}




