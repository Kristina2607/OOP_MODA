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
};

