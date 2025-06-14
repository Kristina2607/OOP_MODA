#pragma once
#include "MyString.h"
#include "Role.h"
#include <fstream>

class User
{
private:
	MyString password;
protected:
	MyString name;
	MyString EGN;
	bool isLoggedIn;
	Role role;

public:
	User(Role role);
	User(std::ifstream& ifs);
	User(const MyString& name, const MyString& password, const MyString& EGN, Role role);

   const MyString& getName() const;
   const MyString& getEGN() const;
   bool getLoggedInStatus() const;
   bool checkPassword(const MyString& password) const;
   bool checkLogData(const MyString& name, const MyString& password);

   virtual void logout();
   virtual void viewProfile() const = 0;
   virtual void help() const = 0;

   virtual User* clone() const = 0;
   Role getRole() const;

   virtual ~User() = default;

   virtual void serialize(std::ofstream& ofs) const;
   virtual void deserialize(std::ifstream& ifs);

};
