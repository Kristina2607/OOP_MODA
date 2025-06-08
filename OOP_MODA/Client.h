#pragma once
#include "User.h"
#include "Cart.h"
#include "Order.h"
#include "RefundRequest.h"
#include "MyString.h"
#include "MyVector.hpp"

class Client :public User
{
private:
	unsigned points = 0;
	double wallet = 0.0;
	Cart cart;
	MyVector<Order> orders;
	Order* lastOrder = nullptr;

public:
	Client() = default;
	Client(double wallet, unsigned points, Cart cart);

	double getWallet() const;
	unsigned getPoints() const;

	virtual void view_profile() const override;
	virtual void help() const override;

	virtual User* clone() const override;
	virtual MyString getRole() const override;
	virtual bool hasPermission(const MyString& action) const override;

	void addToCart(unsigned ID, unsigned quantity);
	void removeFromCart(const MyString& name, unsigned quantity);

	void view_cart() const;
	void clear_cart();

	void applyDiscount();
	void removeDiscount();

	void recieveRefund(double refund);
	void refunded_orders() const;
	bool request_refund(const Business& business);

	void checkBalance() const;
	void checkout();

	void rateOrder(unsigned ProductID, unsigned rating);
	void confirmOrder(size_t index);

	void list_orders() const;
	void order_history() const;
};

