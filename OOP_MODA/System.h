#pragma once
#include "MyVector.hpp"
#include "MyString.h"
#include "HeterogeneousContainer.hpp"
#include "Item.h"
#include "User.h"
#include "Administrator.h"
#include "Business.h"

class System
{
private:
	HeterogeneousContainer<User> users;
	MyVector<Item> items;

	Administrator* admin;
	Business* business;
	User* loggedUser;
	
	System() = default;

public:
	static System& getInstance();

	System(const System& other) = delete;
	System& operator=(const System& other) = delete;

	void run();

	void listProducts() const;
	void viewProduct(unsigned ID) const;

	void login(const MyString& name, const MyString& pass);
	void registerUser (User* newUser);
	void logout();

	void help() const;
	void viewProfile() const;

	
	void confirmOrder(size_t orderIndex) const;
	void checkout() const;
	void redeem(const MyString& code) const;
	void checkBalance() const;
	void applyDiscount() const;
	void removeDiscount() const;
	void addToCart(unsigned ID, unsigned quantity) const;
	void removeFromCart(const MyString& name, unsigned quantity) const;
	void viewCart() const;
	void refundedOrders() const;

	void addItem(const MyString& name, double price, unsigned quantity, const MyString& description) const;
	void removeItem(const MyString& name) const;
	void listPendingOrders() const;
	void listOrders() const;
	void viewRevenue() const;

};

