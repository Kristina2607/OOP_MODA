#pragma once

#include "MyVector.hpp"
#include "Check.h"
#include "Transactions.h"
#include "User.h"
#include "Role.h"
#include "Client.h"
#include "MyString.h"

class Administrator : public User
{
private:
	MyVector <Check> checks;
	MyVector<Transactions> transactions;
	MyVector<Client> clients;


public:
	Administrator(MyString name, MyString password, MyString EGN);

	virtual void viewProfile() const override;
	virtual void help() const override;
	virtual User* clone() const override;

	void sendChecks(unsigned sum, const MyString& code, const MyString& clientEGN);
	void customerInsights() const;
	void viewTransactions() const;
};

