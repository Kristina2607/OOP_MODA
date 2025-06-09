#pragma once
#include "MyVector.hpp"
#include "Item.h"
#include "MyPair.hpp"

class Client;

enum class Status
{
	Pending,
	Shipped,
	Delivered
};

class Order
{
private:
	static unsigned NextOrderID;
	unsigned ID = 0;

	MyVector<MyPair<Item, unsigned>> items;
	Client& client;
	double totalPrice = 0;
	unsigned points = 0;
	Status status;

	bool isRefunded = false;
	bool usedDiscount = false;

public:
	Order() = default;
	Order (MyVector<MyPair<Item, unsigned>> items, Client& client, double totalPrice, unsigned points, Status status);

	double getTotalPrice() const;
	unsigned getPoints() const;
	unsigned getID() const;
	Client& getClient() const;

	void setStatus(Status newStatus);
	const char* statusToString() const;

	void markAsRefunded();
	bool hasUsedDiscount() const;
	bool getIsRefunded() const;

	void printOrder() const;
};
