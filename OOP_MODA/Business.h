#pragma once
#include "User.h"
#include "Item.h"
#include "RefundRequest.h"
#include "MyVector.hpp"
#include "ItemsFilter.h"
#include "ItemsManager.h"
#include "OrderManager.h"

class Order;

class Business :public User
{
private:
	MyVector<RefundRequest> refundRequests;
	ItemsManager items;
	OrderManager orders;
	double totalRevenue;


public:
	Business(std::ifstream& ifs, const MyVector<Client>& clients);
	Business(MyString name, MyString password, MyString EGN);
	
	virtual void viewProfile() const override;
	virtual void help() const override;
	virtual User* clone() const override;

	void removeItem(const MyString& name);
	void addItem(const MyString& name, double price, unsigned quantity, const MyString& description);

	void listProducts() const;
	void viewProduct(unsigned ID) const;
	bool hasProduct(unsigned ID);
	ItemsManager& getItemsManager();

	void listRefunds() const;
	void recieveRefundRequest(RefundRequest* newRequest);
	void approveRefund(size_t index);
	void rejectRefund(size_t index, const MyString& reason);

	void recieveOrderRequest(const Order& order);
	void listOrders() const;
	void listPendingOrders() const;
	void listBestSeliingProducts() const;
	void viewRevenue() const;

	void approveOrder(unsigned ID);
	void rejectOrder(unsigned ID, const MyString& description);

	OrderManager& getOrderManager();

	virtual void serialize(std::ofstream& ofs) const override;
	virtual void deserialize(std::ifstream& ifs) override;
};

