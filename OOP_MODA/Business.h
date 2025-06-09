#pragma once
#include "User.h"
#include "Item.h"
#include "RefundRequest.h"
#include "MyVector.hpp"
#include "ItemsFilter.h"

class Order;

class Business :public User
{
private:
	static Business* obj;

	MyVector<Item> items;
	MyVector<RefundRequest> refundRequests;
	MyVector<Order> orders;
	double totalRevenue;

	Business();

public:
	static Business& getInstance();
	Business(const Business& other) = delete;
	Business& operator=(const Business& other) = delete;
	
	virtual void viewProfile() const override;
	virtual void help() const override;

	virtual User* clone() const override;

	void removeItem(const MyString& name);
	void addItem(const MyString& name, double price, unsigned quantity, const MyString& description);

	void listRefunds() const;
	void addRefund(const RefundRequest& newRequest);
	void approveRefund(size_t index);
	void rejectRefund(size_t index, const MyString& reason);
	bool processRefundRequest(const Order& order) const;

	void list_Orders() const;
	void listPendingOrders() const;
	void listBestSeliingProducts() const;
	void viewRevenue() const;

	void approveOrder(size_t index);
	void rejectOrder(size_t index, const MyString& description);
};

