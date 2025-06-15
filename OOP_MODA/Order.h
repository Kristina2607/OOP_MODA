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

	Client* client;
	MyString clientEGN;

	double totalPrice = 0;
	unsigned points = 0;
	Status status;

	bool isRefunded = false;
	bool usedDiscount = false;

public:
	Order() = default;
	Order (MyVector<MyPair<Item, unsigned>> items, Client* client, double totalPrice, unsigned points, Status status);

	double getTotalPrice() const;
	unsigned getPoints() const;
	unsigned getID() const;

	Client* getClient() const;
	const MyString& getClientEgn() const;
	void setClient(Client* newClient);

	MyVector<MyPair<Item, unsigned>> getItems() const;
	const Item& getProduct(size_t index) const;
	unsigned getProductsCount() const;

	void setStatus(Status newStatus);
	const char* statusToString() const;

	void markAsRefunded();
	bool hasUsedDiscount() const;
	bool getIsRefunded() const;

	void printOrder() const;

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
	
};
