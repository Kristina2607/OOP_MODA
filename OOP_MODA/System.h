#pragma once
#include "MyVector.hpp"
#include "MyString.h"
#include "HeterogeneousContainer.hpp"
#include "Item.h"
#include "Client.h"

class System
{
private:
	HeterogeneousContainer<User> users;
	MyVector<Item> items;

	User* loggedUser;

public:
	void run();

	void list_products() const;
	void view_product(unsigned ID) const;

	void login(const MyString& name, const MyString& pass);
	void registerUser (const MyString& name, const MyString& pass, const MyString& EGN);
	void help();
	void viewProfile();

};

