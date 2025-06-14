#pragma once

#include "MyVector.hpp"
#include "Check.h"
#include "User.h"
#include "Role.h"
#include "Client.h"
#include "MyString.h"

class Administrator : public User
{
private:
	MyVector<Check> checks;
	MyVector<Client> clients;

public:
	Administrator(std::ifstream& ifs);
	Administrator(MyString name, MyString password, MyString EGN);

	virtual void viewProfile() const override;
	virtual void help() const override;
	virtual User* clone() const override;

	void sendChecks(unsigned sum, const MyString& code, Client& client);
	void customerInsights() const;

	virtual void serialize(std::ofstream& ofs) const override;
	virtual void deserialize(std::ifstream& ifs) override;
};

