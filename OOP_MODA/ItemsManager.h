#pragma once
#include "MyVector.hpp"
#include "MyPair.hpp"
#include "Item.h"

class ItemsManager
{
private:
	MyVector<Item> items;

public:
	void viewProduct(unsigned ID) const;
	void listProducts() const;
	size_t getSize() const;

	void addItem(const Item& obj);
	void erase(size_t index);
	bool isAvailable(unsigned ID);
	Item* findByID(unsigned ID);

	Item& getItem(size_t index);
	const Item& getItem(size_t index) const;
	const Item& getLastItem() const;

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
};

