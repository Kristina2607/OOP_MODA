#pragma once
#include "MyString.h"
#include "LoggedUser.h"

class User
{
private:
	MyString password;

protected:
	MyString name;
	MyString EGN;
	bool isLoggedIn;

public:
	User();
	User(const MyString& name, const MyString& password, const MyString& EGN);

   MyString getName() const;
   bool getLoggedInStatus() const;

   virtual void logout();
   virtual void view_profile() const = 0;
   virtual void help() const = 0;

   virtual User* clone() const = 0;
   virtual MyString getRole() const = 0;
   virtual bool hasPermission(const MyString& action) const;

   virtual ~User() = default;
};
