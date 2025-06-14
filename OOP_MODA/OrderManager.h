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
	void removeOrder(size_t index);

	unsigned getSize() const;
	unsigned getTotalSpent() const;
	void refundedOrders() const;

	bool isEmpty();
	Order& getOrder(size_t index) const;
	Order& getOrder(size_t index);
	const Order& getLastOrder() const;

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
};

