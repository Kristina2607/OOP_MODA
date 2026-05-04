#include "Order.h"
#include "Client.h"

unsigned Order::NextOrderID = 1;

Order::Order(MyVector<MyPair<Item, unsigned>> items, Client* client, double totalPrice, unsigned points, Status status)
 :ID(NextOrderID++), items(items), client(client), totalPrice(totalPrice), points(points), status(status), clientEGN(client->getEGN()) {}

double Order::getTotalPrice() const
{
	return totalPrice;
}

unsigned Order::getPoints() const
{
	return points;
}

unsigned Order::getID() const
{
	return ID;
}

Status Order::getOrderStatus() const
{
	return status;
}

Client* Order::getClient() const
{
	return client;
}

const MyString& Order::getClientEgn() const
{
	return clientEGN;
}

void Order::setClient(Client* newClient)
{
	this->client = newClient;
}

MyVector<MyPair<Item, unsigned>> Order::getItems() const
{
	return items;
}

const Item& Order::getProduct(size_t index) const
{
	return items[index].first;
}

unsigned Order::getProductsCount() const
{
	unsigned counter = 0;
	for (size_t i = 0; i < items.getSize(); i++)
	{
		counter++;
	}
	return counter;
}

void Order::setStatus(Status newStatus)
{
	status = newStatus;
}

const char* Order::statusToString() const
{
	switch (status)
	{
	case Status::Pending: return "Pending";
	case Status::Shipped: return "Shipped";
	case Status::Delivered: return "Delivered";
	default: return "Unknown";
	}
}

void Order::markAsRefunded()
{
	isRefunded = true;
}

bool Order::getIsRefunded() const
{
	return isRefunded;
}

void Order::printOrder() const
{
	std::cout << client->getName() << " - ";
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (i != items.getSize() - 1)
		{
			std::cout << " - ";
		}
		std::cout << items[i].second << "x" << items[i].first.getName() << ",";
	}
	std::cout << totalPrice << " BGN";
	std::cout << " - " << statusToString() << std::endl;
}

void Order::serialize(std::ofstream& ofs) const
{
	ofs.write((const char*)(&ID), sizeof(unsigned));
	ofs.write((const char*)(&points), sizeof(unsigned));
	ofs.write((const char*)(&totalPrice), sizeof(double));
	ofs.write((const char*)(&status), sizeof(Status));
	ofs.write((const char*)(&isRefunded), sizeof(bool));
	MyString::writeStringToFile(ofs, clientEGN);

	size_t itemsCount = items.getSize();
	ofs.write((const char*)(&itemsCount), sizeof(itemsCount));
	for (size_t i = 0; i < itemsCount; i++)
	{
		items[i].first.serialize(ofs);
		unsigned quantity = items[i].second;
		ofs.write((const char*)(&quantity), sizeof(quantity));
	}
}

void Order::deserialize(std::ifstream& ifs)
{
	ifs.read((char*)(&ID), sizeof(unsigned));
	ifs.read((char*)(&points), sizeof(unsigned));
	ifs.read((char*)(&totalPrice), sizeof(double));
	ifs.read((char*)(&status), sizeof(Status));
	ifs.read((char*)(&isRefunded), sizeof(bool));
	clientEGN = MyString::readStringFromFile(ifs);

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
	this->client = client;
}


