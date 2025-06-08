#pragma once
#include "User.h"
#include "Item.h"
#include "RefundRequest.h"
#include "MyVector.hpp"

class User;
class Business :public User
{
private:
	MyVector<Item> items;
	MyVector<RefundRequest> refundRequests;
	MyVector<Order> orders;
	double totalRevenue;

public:
	virtual void view_profile() const override;
	virtual void help() const override;

	virtual User* clone() const override;
	virtual MyString getRole() const override;

	void removeItem(const MyString& name);
	void addItem(const MyString& name, double price, unsigned quantity, const MyString& description);

	void listRefunds() const;
	void approveRefund(size_t index);
	void rejectRefund(size_t index, const MyString& reason);
	bool processRefundRequest(const Order& order);

	void list_orders() const;
	void list_pending_orders() const;
	void view_revenue() const;

	void approve_order(size_t index);
	void reject_order(size_t index, const MyString& description);
};

