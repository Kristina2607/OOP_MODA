#pragma once
#include "Item.h"
#include "MyVector.hpp"
#include "MyPair.hpp"

class Client;
class Order;

class Cart
{
	MyVector<MyPair<Item,unsigned>> items;
	Client& client;
	double totalPrice = 0.0;

public:
	Cart() = default;
	Cart(Client& client);
	Cart(const MyVector<MyPair<Item, unsigned>>& items, Client& client, double totalPrice);

	void addToCart(unsigned ID, unsigned quantity);
	void removeFromCart(const MyString& name, unsigned quantity);

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
};
