#include "Cart.h"
#include "Order.h"
#include "Client.h"

Cart::Cart(Client* client) : client(client) {}

Cart::Cart(const MyVector<MyPair<Item, unsigned>>& items, Client* client,double totalPrice, bool hasUsedDiscount) 
	: client(client), totalPrice(totalPrice), clientEGN(client->getEGN()), hasUsedDiscount(false)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		this->items.push_back(items[i]);
	}
	updateTotalPrice();
}

void Cart::addToCart(const Item& item, unsigned quantity)
{
	if (quantity == 0)
	{
		throw std::invalid_argument("Quantity can not be zero.");
	}

	items.push_back({ item, quantity });
	totalPrice += item.getPrice() * quantity;
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

void Cart::setClient(Client* client)
{
	this->client = client;
}

void Cart::view_cart() const
{
	std::cout << "Items in cart:" << std::endl;
	for (size_t i = 0; i < items.getSize(); i++)
	{
		std::cout << (i + 1) << ". " << items[i].second << "x " << items[i].first.getName() << " | " 
			<< (items[i].first.getPrice() * items[i].second) << " BGN" << std::endl;
	}
	std::cout << "Total price: " << totalPrice << " BGN" << std::endl;
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
	if (hasUsedDiscount)
	{
		throw std::logic_error("You can not use discount twice.");
	}
	if (currentDiscount>maxAllowedDiscount)
	{
		throw std::logic_error("You can not exceed more than 50% of the price.");
	}
	totalPrice -= currentDiscount;
	hasUsedDiscount = true;
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
		currentDiscount=maxAllowedeDiscount;
	}
	return (totalPrice - currentDiscount);
}

const MyVector<MyPair<Item, unsigned>>& Cart::getItems() const
{
	return items;
}

Order Cart::toOrder()
{
	if (!client)
	{
		throw std::logic_error("Cart has no associated client!");
	}
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

void Cart::serialize(std::ofstream& ofs) const
{
	MyString::writeStringToFile(ofs, clientEGN);
	ofs.write((const char*)(&totalPrice), sizeof(totalPrice));
	size_t itemsCount = items.getSize();
	ofs.write((const char*)(&itemsCount), sizeof(itemsCount));
   
	for (size_t i = 0; i < itemsCount; i++)
	{
		items[i].first.serialize(ofs); 
		unsigned quantity = items[i].second;
		ofs.write((const char*)(&quantity), sizeof(quantity));
	}
}

void Cart::deserialize(std::ifstream& ifs, Client* client)
{
	clientEGN = MyString::readStringFromFile(ifs);
	ifs.read((char*)(&totalPrice), sizeof(totalPrice));
	size_t itemsCount = 0;
	ifs.read((char*)(&itemsCount), sizeof(itemsCount));

	items.clear();
	for (size_t i = 0; i < itemsCount; i++)
	{
		Item item;
		item.deserialize(ifs);
		unsigned quantity = 0;
		ifs.read((char*)(&quantity), sizeof(quantity));

		items.push_back(MyPair<Item, unsigned>(item, quantity));
	}
	this->client=client;
}



