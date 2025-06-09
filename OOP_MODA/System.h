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
	
	System() = default;

public:
	static System& getInstance();

	System(const System& other) = delete;
	System& operator=(const System& other) = delete;

	void run();

	void list_products() const;
	void view_product(unsigned ID) const;

	void login(const MyString& name, const MyString& pass);
	void registerUser (User* newUser);
	void help();
	void viewProfile();

	void confirmOrder(size_t orderIndex) const;
	void checkout() const;
	void checkBalance() const;

};

