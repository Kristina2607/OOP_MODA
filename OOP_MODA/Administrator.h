#pragma once

#include "MyVector.hpp"
#include "Check.h"
#include "Transactions.h"
#include "User.h"
#include "Role.h"
#include "Client.h"

class Administrator : public User
{
private:
	MyVector <Check> checks;
	MyVector<Transactions> transactions;
	MyVector<Client> clients;

public:
	Administrator() = default;
	Administrator(const MyString& name, const MyString& password, const MyString& EGN, Role role);

	void send_checks(unsigned sum, const MyString& code, const MyString& clientEGN);
	void customer_insignts(const Client& client) const;
	void view_transactions() const;
};

