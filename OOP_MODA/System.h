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
	Business* getBusiness() const;
	Administrator* getAdministrator() const;

	System(const System& other) = delete;
	System& operator=(const System& other) = delete;
	~System();

	void run();

	void login(const MyString& name, const MyString& pass);
	void registerUser (User* newUser);
	void logout();

	void help() const;
	void viewProfile() const;

	//Client commands:
	void confirmOrder(size_t orderIndex) const;
	void checkout();
	void redeem(const MyString& code) const;
	void checkBalance() const;
	void applyDiscount() const;
	void removeDiscount() const;
	void addToCart(unsigned ID, unsigned quantity) const;
	void removeFromCart(const MyString& name, unsigned quantity) const;
	void viewCart() const;
	void viewProduct(unsigned ID) const;
	void listProducts() const;
	void refundedOrders() const;
	void requestRefund(Business* business, const MyString& reason) const;

	//Business commands:
	void addItem(const MyString& name, double price, unsigned quantity, const MyString& description) const;
	void removeItem(const MyString& name) const;
	void listPendingOrders() const;
	void listOrders() const;
	void viewRevenue() const;
	void approveRefund(size_t index) const;
	void listBestSellingProducts() const;

	//Administartor commands:
	void sendCheck(unsigned sum, const MyString& code, const MyString& clientEGN) const;
	void customerInsights() const;
};

