#include "Cart.h"
#include "Order.h"
#include "Client.h"

Cart::Cart(Client* client) : client(client) {}

Cart::Cart(const MyVector<MyPair<Item, unsigned>>& items, Client* client, double totalPrice) : client(client), totalPrice(totalPrice)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		this->items.push_back(items[i]);
	}
	updateTotalPrice();
}

void Cart::addToCart(unsigned ID, unsigned quantity)
{
	if (quantity == 0)
	{
		throw std::invalid_argument("Quantity can not be zero.");
	}
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i].first.getId() == ID)
		{
			items[i].second += quantity;
			totalPrice += items[i].first.getPrice() * quantity;
			return;
		}
	}
	throw std::invalid_argument("Item with this ID number is not found in the cart.");
}

void Cart::removeFromCart(const MyString& name, unsigned quantity)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i].first.getName() == name)
		{
			if (quantity >= items[i].second)
			{
				totalPrice -= items[i].first.getPrice() * items[i].second;
				items.erase(i);
			}
			else
			{
				totalPrice -= items[i].first.getPrice() * quantity;
				items[i].second -= quantity;
			}
			return;
		}
	}
	throw std::invalid_argument("Item with this name is not found in the cart.");
}

void Cart::view_cart() const
{
	std::cout << "Items in cart:" << std::endl;
	for (size_t i = 0; i < items.getSize(); i++)
	{
		std::cout << (i + 1) << ". " << items[i].second << "x " << items[i].first.getName() << " | " 
			<< (items[i].first.getPrice() * items[i].second) << " BGN" << std::endl;
	}
	std::cout << "Total price without the discount: " << totalPrice << " BGN" << std::endl;
	std::cout << "Total price with the discount: " << getDiscountedPrice() << " BGN" << std::endl;
}

void Cart::clear_cart()
{
	items.clear();
	totalPrice = 0.0;
}

void Cart::applyDiscount()
{
	double maxAllowedDiscount = totalPrice * 0.5;
	double currentDiscount = client->getPoints() * 0.01;
	if (currentDiscount>maxAllowedDiscount)
	{
		std::cout << "The total price remains the same." << std::endl;
		throw std::logic_error("You can not exceed more than 50% of the price.");
	}
	totalPrice -= currentDiscount;
}

void Cart::removeDiscount()
{
	totalPrice += client->getPoints() * 0.01;
	std::cout << "The discount is removed." << std::endl;
}

double Cart::getTotalPrice() const
{
	return totalPrice;
}

double Cart::getDiscountedPrice() const
{
	double currentDiscount = 0.01 * client->getPoints();
	double maxAllowedeDiscount = 0.5 * totalPrice;
	if (currentDiscount > maxAllowedeDiscount)
	{
		return totalPrice;
	}
	return (totalPrice - currentDiscount);
}

const MyVector<MyPair<Item, unsigned>>& Cart::getItems() const
{
	return items;
}

Order Cart::toOrder()
{
	return Order(items, client, totalPrice, client->getPoints(), Status::Pending);
}

MyVector<MyPair<Item, unsigned>>&& Cart::moveItems()
{
	return std::move(items);
}


void Cart::updateTotalPrice()
{
	totalPrice = 0.0;
	for (size_t i = 0; i < items.getSize(); i++)
	{
		totalPrice += items[i].first.getPrice() * items[i].second;
	}
}



