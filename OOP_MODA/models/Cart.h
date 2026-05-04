#pragma once
#include "Item.h"
#include "MyVector.hpp"
#include "MyPair.hpp"
#include "MyString.h"
#include <fstream>

class Client;
class Order;

class Cart
{
	MyVector<MyPair<Item, unsigned>> items;
	Client* client;  //observer pointer -> no rule of five
	MyString clientEGN;
	double totalPrice = 0.0;
	bool hasUsedDiscount = false;

public:
	Cart() = default;
	Cart(Client* client);
	Cart(const MyVector<MyPair<Item, unsigned>>& items, Client* client,double totalPrice, bool hasUsedDiscount);

	void addToCart(const Item& item, unsigned quantity);
	void removeFromCart(const MyString& name, unsigned quantity);
	void setClient(Client* client);

	void view_cart() const;
	void clear_cart();

	void applyDiscount();
	void removeDiscount();

	double getTotalPrice() const;
	double getDiscountedPrice() const;
	const MyVector<MyPair<Item, unsigned>>& getItems() const;

	Order toOrder();
	MyVector<MyPair<Item, unsigned>>&& moveItems();
	void updateTotalPrice();

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs, Client* client);
};
