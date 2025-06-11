#pragma once
#include "MyVector.hpp"
#include "MyPair.hpp"
#include "Item.h"

class ItemsManager
{
private:
	MyVector<MyPair<Item, unsigned>> items;

public:
	void viewProduct(unsigned ID) const;
	void listProducts() const;
};

