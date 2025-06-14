#pragma once
#include "MyVector.hpp"
#include "MyString.h"
#include "ItemsManager.h"
#include "User.h"
#include "Client.h"
#include "Administrator.h"
#include "Business.h"

class System
{
private:
	MyVector<Client> clients;
	Administrator* admin;
	Business* business;
	User* loggedUser = nullptr;
	
	System();
	
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

	void saveSystem();
	void saveBusiness();
	void saveClients();
	void saveAdministrator();

	void loadSystem();
	void loadAdministrator();
	void loadBusiness();
	void attachClientsToCheck();//ot cseki klient vzimam check i go pulnq v admina
	void attachClientsToOrders();
	void loadClients();

	Client& findClientByEgn(const MyString& EGN);
	const Client& findClientByEgn(const MyString& EGN) const;

	//Client commands:
	void confirmOrder(size_t orderIndex);
	void listOrdersClient() const;
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
	void orderHistory() const;
	void requestRefund(const MyString& reason);

	//Business commands:
	void addItem(const MyString& name, double price, unsigned quantity, const MyString& description);
	void removeItem(const MyString& name);
	void listPendingOrders() const;
	void listBestSellingProducts() const;
	void listOrders() const;
	void approveOrder(size_t index);
	void rejectOrder(size_t index, const MyString& reason);
	void listRefunds() const;
	void viewRevenue() const;
	void approveRefund(size_t index);
	void rejectRefund(size_t index, const MyString& reason);


	//Administartor commands:
	void sendCheck(unsigned sum, const MyString& code, const MyString& clientEGN);
	void customerInsights() const;
};

