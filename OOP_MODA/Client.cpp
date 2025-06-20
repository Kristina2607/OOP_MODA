#include "Client.h"
#include "Order.h"
#include "Cart.h"
#include "Role.h"
#include "System.h"

Client::Client() : User(Role::Client) {}

Client::Client(const MyString& name, const MyString& password, const MyString& EGN)
	: User(name, password, EGN, Role::Client), cart() {}

Client::Client(const MyString& name, const MyString& password, const MyString& EGN,
	double wallet, unsigned points, Cart cart) : User(name, password, EGN, Role::Client), wallet(wallet), points(points), cart(cart)
{ }

double Client::getWallet() const
{
	return wallet;
}

unsigned Client::getPoints() const
{
	return points;
}

const MyString& Client::getEGN() const
{
	return EGN;
}

const Check& Client::getCheck(size_t index) const
{
	return recievedChecks[index];
}

Cart& Client::getCart()
{
	return cart;
}

MyVector<Check>& Client::getChecks()
{
	return recievedChecks;
}

OrderManager& Client::getOrderManager()
{
	return orders;
}

const OrderManager& Client::getOrderManager() const
{
	return orders;
}

unsigned Client::getOrdersCount() const
{
	return orders.getSize();
}

unsigned Client::getTotalSpent() const
{
	return orders.getTotalSpent();
}

void Client::viewProfile() const
{
	std::cout << "Client" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Ponts: " << points << std::endl;
	std::cout << "Balance in your wallet: " << wallet << std::endl;
}

void Client::help() const
{
	std::cout << std::endl;
	std::cout << "You are allowed to:" << std::endl;

	std::cout << "> check_balance" << std::endl;
	std::cout << "> request_refund" << std::endl;
	std::cout << "> redeem" << std::endl;

	std::cout << "> list-orders" << std::endl;
	std::cout << "> order_history" << std::endl;
	std::cout << "> refunded_orders" << std::endl;

	std::cout << "> view_product " << std::endl;
	std::cout << "> apply_discount" << std::endl;
	std::cout << "> remove_discount" << std::endl;
	std::cout << "> confirm_order" << std::endl;
	std::cout << "> rate" << std::endl;

	std::cout << "> list_products" << std::endl;
	std::cout << "> filter_by_rating" << std::endl;
	std::cout << "> filter_by_price (desc)" << std::endl;
	std::cout << "> filter_by_price (asc)" << std::endl;
	std::cout << "> filter_by_alphabetical_order" << std::endl;

	std::cout << "> add_to_cart" << std::endl;
	std::cout << "> remove_from_cart" << std::endl;
	std::cout << "> view_cart" << std::endl;
	std::cout << "> checkout" << std::endl;
}

User* Client::clone() const
{
	return new Client(*this);
}

void Client::addToCart(const Item& item, unsigned quantity)
{
	cart.addToCart(item, quantity);
	std::cout << "You successfully added " << quantity << " x " << item.getName() << " to your cart."<<std::endl;
}

void Client::removeFromCart(const MyString& name, unsigned quantity)
{
	cart.removeFromCart(name, quantity);
	std::cout << "You successfully removed " << quantity << " x " << name << " from your cart."<<std::endl;
}

void Client::viewCart() const
{
	cart.view_cart();
}

void Client::clearCart()
{
	cart.clear_cart();
}

void Client::applyDiscount()
{
	cart.applyDiscount();
}

void Client::removeDiscount()
{
	cart.removeDiscount();
}

void Client::checkBalance() const
{
	std::cout << "Current balance: " << wallet << " BGN" << std::endl;
	std::cout << "Loyalty points: " << points << std::endl;
}

void Client::redeemCheck(const MyString& code)
{
	Check* targetCheck = nullptr;

	for (size_t i = 0; i < recievedChecks.getSize(); i++)
	{
		if (recievedChecks[i].isValidCode(code) && !recievedChecks[i].getIsRedeemed()) {
			targetCheck = &recievedChecks[i];
			break;
		}
	}
	if (!targetCheck)
	{
		throw std::runtime_error("No valid check found with this code!");
	}

	targetCheck->redeem();
	wallet += targetCheck->getSum();

	std::cout << "Successfully redeemed check for " << targetCheck->getSum() << " BGN. " << std::endl;
}

void Client::recieveCheck(const Check& check)
{
	if (check.getEGN() != this->getEGN())
	{
		throw std::runtime_error("Check recipient EGN doesn't match!");
	}
	recievedChecks.push_back(check);
}

void Client::recieveRefund(double refund)
{
	wallet += refund;
}

void Client::refundedOrders() const
{
	orders.refundedOrders();
}

RefundRequest* Client::requestRefund(const MyString& reason)
{
	if (orders.isEmpty())
	{
		throw std::logic_error("There are no orders. ");
	}
	const Order& lastOrder = orders.getLastOrder();

	RefundRequest* request = new RefundRequest(reason, &lastOrder, const_cast<Client*>(this));
	this->points = 0;
	std::cout << "Refund request submitted for last order (" << lastOrder.getTotalPrice() <<
		" BGN). All loyalty points have been removed." << std::endl;

	return request;
}

Order& Client::checkout()
{
	double totalPrice = cart.getTotalPrice();
	if (wallet < totalPrice)
	{
		throw std::logic_error("Not enough money in the wallet.");
	}

	wallet -= totalPrice;
	Order newOrder = cart.toOrder();

	orders.addOrder(newOrder); 
	cart.clear_cart();

	std::cout << "Your order is placed successfully! Now is waiting for confirmation." << std::endl;

	return orders.getLastOrder();
}

void Client::rateOrder(unsigned productID, unsigned rating)
{
	if (rating < 1 || rating > 5)
	{
		std::cout << "Rating must be between 1 and 5." << std::endl;
		return;
	}
	
	bool hasPurchased = false;
	for (size_t i = 0; i < orders.getOrders().getSize(); i++)
	{
		const Order& order = orders.getOrders()[i];

		const MyVector<MyPair<Item, unsigned>>& items = order.getItems();
		for (size_t j = 0; j < items.getSize(); j++)
		{
			if (items[j].first.getID() == productID)
			{
				hasPurchased = true;
				break;
			}
		}
		if (hasPurchased)
		{
			break;
		}
	}

	if (!hasPurchased)
	{
		throw std::logic_error("You haven't purchased this item yet.");
		return;
	}
}

void Client::confirmOrder(unsigned ID)
{
	Order* order = orders.getOrderById(ID);
	if (!order)
	{
		throw std::invalid_argument("Invalid argument");
	}
	else if (order->statusToString() != "Shipped")
	{
		throw std::logic_error("This order is not shipped yet.");
	}
	order->setStatus(Status::Delivered);
	System::getInstance().getBusiness()->getOrderManager().getOrderById(ID)->setStatus(Status::Delivered);

	unsigned earnedPoints = order->getTotalPrice() * 5;
	points += earnedPoints;
	std::cout << "Order confirmed as received. You earned " << earnedPoints << " points." << std::endl;
}

void Client::listOrders() const
{
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		if (orders.getOrder(i).statusToString() == "Shipped")
		{
			orders.getOrder(i).printOrder();
		}
	}
}

void Client::orderHistory() const
{
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		if (System::getInstance().getBusiness()->getOrderManager().getOrder(i).getOrderStatus() == Status::Delivered)
		{
			orders.getOrder(i).printOrder();
		}
	}
}

void Client::listProducts() const
{
	Business* business = System::getInstance().getBusiness();
	if (business)
	{
		business->listProducts();
	}
	else
	{
		std::cout << "No business available." << std::endl;
	}
}

void Client::viewProduct(unsigned ID) const
{
	Business* business = System::getInstance().getBusiness();
	if (business)
	{
		business->viewProduct(ID);
	}
	else
	{
		std::cout << "No business available." << std::endl;
	}
}

void Client::serialize(std::ofstream& ofs) const
{
	User::serialize(ofs);
	ofs.write((const char*)(&points), sizeof(unsigned));
	ofs.write((const char*)(&wallet), sizeof(double));

	cart.serialize(ofs);
	orders.serialize(ofs);

	size_t checksCount = recievedChecks.getSize();
	ofs.write((const char*)(&checksCount), sizeof(checksCount));
	for (size_t i = 0; i < checksCount; i++)
	{
		recievedChecks[i].serialize(ofs);
	}
}

void Client::deserialize(std::ifstream& ifs)
{
	User::deserialize(ifs);
	ifs.read((char*)(&points), sizeof(unsigned));
	ifs.read((char*)(&wallet), sizeof(double));

	cart.deserialize(ifs, this);
	orders.deserialize(ifs);

	size_t checksCount = 0;
	ifs.read((char*)&checksCount, sizeof(checksCount));
	recievedChecks.clear();
	for (size_t i = 0; i < checksCount; i++)
	{
		Check check;
		check.deserialize(ifs);
		recievedChecks.push_back(check);
	}

}
