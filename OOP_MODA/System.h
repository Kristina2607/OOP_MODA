#pragma once
#include "MyVector.hpp"
#include "MyString.h"
#include "HeterogeneousContainer.hpp"
#include "Item.h"
#include "User.h"
#include "Client.h"
#include "Administrator.h"
#include "Business.h"

class System
{
private:
	MyVector<Client> clients;
	MyVector<Item> items;
	Administrator* admin;
	Business* business;
	User* loggedUser = nullptr;
	
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
	void registerUser (const MyString& name, const MyString& password, const MyString& EGN, Role role);
	void logout();

	void help() const;
	void viewProfile() const;

	//Client commands:
	void confirmOrder(size_t orderIndex);
	void checkout();
	void redeem(const MyString& code);
	void checkBalance() const;
	void applyDiscount();
	void removeDiscount();
	void addToCart(unsigned ID, unsigned quantity);
	void removeFromCart(const MyString& name, unsigned quantity);
	void viewCart() const;
	void viewProduct(unsigned ID) const;
	void listProducts() const;
	void refundedOrders() const;
	void requestRefund(const MyString& reason);

	//Business commands:
	void addItem(const MyString& name, double price, unsigned quantity, const MyString& description);
	void removeItem(const MyString& name);
	void listPendingOrders() const;
	void listOrders() const;
	void viewRevenue() const;
	void approveRefund(size_t index);
	void rejectRefund(size_t index, const MyString& reason);
	void listBestSellingProducts() const;

	//Administartor commands:
	void sendCheck(unsigned sum, const MyString& code, const MyString& clientEGN);
	void customerInsights() const;
};

