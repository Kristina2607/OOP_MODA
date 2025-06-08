#pragma once
#include "MyString.h"

class Item
{
private:
	static unsigned nextID;
	unsigned ID = 0;

	MyString name;
	MyString description;

	double price = 0;
	double rating = 0;
	unsigned quantity = 0;
	bool availability = false;

public:
	Item();
	Item(const MyString& name, const MyString& description, double price, double rating, unsigned quantity, bool availability);

	unsigned getId() const;
	MyString getName() const;
	double getPrice() const;
	unsigned getRating() const;
	MyString getDescription() const;

	void printItem() const;
};

