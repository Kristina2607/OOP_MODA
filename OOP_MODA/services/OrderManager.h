#pragma once
#include "Order.h"
#include "MyVector.hpp"
#include "MyPair.hpp"

class OrderManager
{
private:
	MyVector<Order> orders;

public:
	void removeID(unsigned ID);
	void addOrder(const Order& newOrder);
	void removeOrder(size_t index);

	unsigned getSize() const;
	unsigned getTotalSpent() const;
	void refundedOrders() const;

	bool isEmpty();
	const Order& getOrder(size_t index) const;
	Order& getOrder(size_t index);
	Order* getOrderById(unsigned ID);
	Order& getLastOrder();
	const MyVector<Order>& getOrders() const;

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
};

