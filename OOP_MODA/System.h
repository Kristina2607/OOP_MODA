#pragma once
#include "MyVector.hpp"
#include "Item.h"
#include "UserManager.h"

class System
{
private:
	UserManager userMnager;
	MyVector<Item> items;

public:
	void list_products() const;
	void view_product(unsigned ID) const;

	void login() const;
};

