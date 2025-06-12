#pragma once
#include "Order.h"
#include "MyVector.hpp"
#include "MyPair.hpp"

class OrderManager
{
private:
	MyVector<Order> orders;
public:
	void removeID(size_t ID);
	void addOrder(const Order& newOrder);

	unsigned getCounter() const;
	unsigned getTotalSpent() const;
	void refundedOrders() const;

	bool isEmpty();
	Order& getOrder(size_t index) const;
	const Order& getLastOrder() const;
};

