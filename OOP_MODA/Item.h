#pragma once
#include "MyString.h"

class Item
{
protected:
	unsigned totalSales = 0;
private:
	static unsigned nextID;
	unsigned ID = 0;

	MyString name;
	MyString description;

	double price = 0;
	double rating = 0;
	bool availability = false;

	unsigned initialQuantity = 0;
	unsigned currentQuantity = 0;

public:
	Item();
	Item(const MyString& name, const MyString& description, double price, double rating, unsigned initialQuantity, bool availability);

	unsigned getId() const;
	MyString getName() const;
	double getPrice() const;
	unsigned getRating() const;
	MyString getDescription() const;

	unsigned getInitialQuantity() const;
	unsigned getCurrentQuantity() const;
	void increaseQuantity(unsigned amount);

	unsigned getTotalSales() const;
	void addSales(unsigned quantity);

	void printItem() const;

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
};

