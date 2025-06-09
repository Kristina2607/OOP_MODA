#pragma once
#include "MyString.h"

class Transactions
{
private:
	MyString from;
	MyString to;
	unsigned sum;

public:
	Transactions() = default;
	Transactions(const MyString& reciever, const MyString& sender, unsigned sum);
	void printTransactions() const;
};

