#pragma once
#include "User.h"
#include "RefundRequest.h"
#include "Check.h"
#include "Cart.h"
#include "MyString.h"
#include "MyVector.hpp"
#include "Business.h"
#include "OrderManager.h"

class Client :public User
{
private:
	unsigned points = 0;
	double wallet = 0.0;
	Cart cart;
	MyVector<Check> recievedChecks;
	OrderManager orders;

public:
	Client();
	Client(const MyString& name, const MyString& password, const MyString& EGN);
	Client(const MyString& name, const MyString& password, const MyString& EGN, double wallet, unsigned points, Cart cart);

	double getWallet() const;
	unsigned getPoints() const;
	const MyString& getEGN() const;
	const Check& getCheck(size_t index) const;
	Cart& getCart();

	MyVector<Check>& getChecks();
	OrderManager& getOrderManager();
	const OrderManager& getOrderManager() const;

	unsigned getOrdersCount() const;
	unsigned getTotalSpent() const;

	virtual void viewProfile() const override;
	virtual void help() const override;

	virtual User* clone() const override;

	void addToCart(const Item& item, unsigned quantity);
	void removeFromCart(const MyString& name, unsigned quantity);

	void viewCart() const;
	void clearCart();

	void applyDiscount();
	void removeDiscount();

	void recieveRefund(double refund);
	void refundedOrders() const;
	RefundRequest* requestRefund(const MyString& reason);

	void checkBalance() const;
	Order& checkout();

	void redeemCheck(const MyString& check);
	void recieveCheck(const Check& check);

	void rateOrder(unsigned productID, unsigned rating);
	void confirmOrder(unsigned ID);

	void listOrders() const;
	void orderHistory() const;

	void listProducts() const;
	void viewProduct(unsigned ID) const;

	virtual void serialize(std::ofstream& ofs) const override;
	virtual void deserialize(std::ifstream& ifs) override;
};

