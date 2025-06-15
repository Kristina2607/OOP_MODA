#include "Business.h"
#include "Order.h"
#include "Client.h"
#include "Role.h"

Business::Business(std::ifstream& ifs, const MyVector<Client>& clients) :User(ifs)
{
	deserialize(ifs);
	for (size_t i = 0; i < clients.getSize(); i++)
	{
		const OrderManager& orderManager = clients[i].getOrderManager();
		for (size_t j = 0; j < orderManager.getSize(); j++)
		{
			orders.addOrder(orderManager.getOrder(j));
		}
	}
}

Business::Business(MyString name, MyString password, MyString EGN)
	: User(name, password, EGN, Role::Business) {}

void Business::viewProfile() const
{
	std::cout << "Business profile" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "EGN: " << this->EGN << std::endl;
}

void Business::help() const
{
	std::cout << "You are allowed to:" << std::endl;

	std::cout << "> add_item" << std::endl;
	std::cout << "> remove_item." << std::endl;
	std::cout << "> view_revenue" << std::endl;
	std::cout << "> approve_order" << std::endl;
	std::cout << "> reject_order" << std::endl;

	std::cout << "> list_orders" << std::endl;
	std::cout << "> list_best_selling_products" << std::endl;
	std::cout << "> list_pending_orders" << std::endl;

	std::cout << "> list_refunds" << std::endl;
	std::cout << "> approve_refunds" << std::endl;
	std::cout << "> reject_refunds" << std::endl;
}

User* Business::clone() const
{
	throw std::logic_error("Cannot clone business");
}

void Business::removeItem(const MyString& name)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items.getItem(i).getName() == name)
		{
			items.erase(i);
			std::cout << name << " is removed successffully." << std::endl;
			return;
		}
	}
	throw std::invalid_argument("Invalid name");
}

void Business::addItem(const MyString& name, double price, unsigned quantity, const MyString& description)
{
	Item newItem = Item(name, description, price, 0, quantity, 1);
	items.addItem(newItem);
	std::cout << name << " is added successffully." << std::endl;
}

void Business::listProducts() const
{
	items.listProducts();
}

void Business::viewProduct(unsigned ID) const
{
	items.viewProduct(ID);
}

bool Business::hasProduct(unsigned ID)
{
	return items.isAvailable(ID);
}

const ItemsManager& Business::getItemsManager() const
{
	return items;
}

void Business::viewRevenue() const
{
	std::cout << "Total reveneue:" << orders.getTotalSpent() << std::endl;
}

void Business::approveOrder(unsigned ID)
{
	Order* order = orders.getOrderById(ID);
	if (!order)
	{
		throw std::invalid_argument("No order with such ID exists!");
	}
	order->setStatus(Status::Shipped);
	order->getClient()->getOrderManager().getOrderById(ID)->setStatus(Status::Shipped);
	
	std::cout << "Order #" << ID << " is approved and shipped. " << std::endl;
}

void Business::rejectOrder(unsigned ID, const MyString& description)
{
	Order* order = orders.getOrderById(ID);
	if (!order)
	{
		throw std::invalid_argument("No order with such ID exists!");
	}
	order->getClient()->recieveRefund(order->getTotalPrice());
	order->getClient()->getOrderManager().removeID(ID);
	orders.removeOrder(ID);
	std::cout << "Order is rejected. Reason: " << description << std::endl;
}

OrderManager& Business::getOrderManager()
{
	return orders;
}

void Business::serialize(std::ofstream& ofs) const
{
	User::serialize(ofs);
	int roleValue = (int)role;
	ofs.write((const char*)&roleValue, sizeof(int));
	items.serialize(ofs);

	size_t requestsCount = refundRequests.getSize();
	ofs.write(reinterpret_cast<const char*>(&requestsCount), sizeof(requestsCount));
	for (size_t i = 0; i < requestsCount; i++)
	{
		refundRequests[i].serialize(ofs);
	}
	orders.serialize(ofs);

	ofs.write((const char*)&totalRevenue, sizeof(double));
}

void Business::deserialize(std::ifstream& ifs)
{
	int roleValue = 0;
	ifs.read((char*)&roleValue, sizeof(int));
	this->role = (Role)roleValue;
	items.deserialize(ifs);

	size_t checksCount = 0;
	ifs.read(reinterpret_cast<char*>(&checksCount), sizeof(checksCount));
	refundRequests.clear();
	for (size_t i = 0; i < checksCount; i++)
	{
		RefundRequest request;
		request.deserialize(ifs);
		refundRequests.push_back(request);
	}
	orders.deserialize(ifs);
	ifs.read((char*)&totalRevenue, sizeof(double));
}

void Business::listRefunds() const
{
	for (size_t i = 0; i < refundRequests.getSize(); i++)
	{
		if (refundRequests[i].getIsProcessed() != 1)
		{
			refundRequests[i].printRefundRequest();
		}
	}
}

void Business::recieveRefundRequest(RefundRequest* newRequest)
{
	refundRequests.push_back(*newRequest);
}

void Business::approveRefund(size_t index)
{
	if (index >= refundRequests.getSize())
	{
		throw std::invalid_argument("Invalid index.");
	}
	RefundRequest& request = refundRequests[index];
	request.approve();

	const Order* order = request.getOrder();
	const MyVector<MyPair<Item, unsigned>>& returnedItems = order->getItems();
	for (size_t i = 0; i < returnedItems.getSize(); i++)
	{
		const MyString& name = returnedItems[i].first.getName();
		unsigned quantity = returnedItems[i].second;

		for (size_t j = 0; j < items.getSize(); j++)
		{
			if (items.getItem(j).getName() == name)
			{
				items.getItem(j).increaseQuantity(quantity);
				break;
			}
		}
	}

	request.getClient()->recieveRefund(request.getOrder()->getTotalPrice());
	request.getClient()->getOrderManager().removeOrder(order->getID());
	refundRequests.erase(index);
	std::cout << "Refund is approved. The sum is returned to " << request.getClient()->getName();
}

void Business::rejectRefund(size_t index, const MyString& reason)
{
	if (index >= refundRequests.getSize())
	{
		throw std::invalid_argument("Invalid index.");
	}
	RefundRequest& request = refundRequests[index];
	request.reject();

	refundRequests.erase(index);
	std::cout << "Refund is rejected. Reason: " << reason << std::endl;
}

void Business::recieveOrderRequest(const Order& order)
{
	orders.addOrder(order);
}

void Business::listOrders() const
{
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		std::cout << (i + 1) << ".";
		orders.getOrder(i).printOrder();
	}
}

void Business::listPendingOrders() const
{
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		if (orders.getOrder(i).statusToString() == "Pending")
		{
			std::cout << (i + 1) << ". ";
			orders.getOrder(i).printOrder();
		}
	}
}

void Business::listBestSeliingProducts() const
{
	MyVector <MyPair<const Item*, unsigned>> temp;
	for (size_t i = 0; i < items.getSize(); i++)
	{
		unsigned initialQuantity = items.getItem(i).getInitialQuantity();
		unsigned currentQuantity = items.getItem(i).getCurrentQuantity();
		unsigned soldQuantity = initialQuantity - currentQuantity;
		if (soldQuantity > 0)
		{
			MyPair<const Item*, unsigned> pair(&items.getItem(i), soldQuantity);
			temp.push_back(pair);
		}
	}
	for (size_t i = 0; i < temp.getSize(); i++)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; j < temp.getSize(); j++)
		{
			if (temp[i].second < temp[j].second)
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			std::swap(temp[minIndex], temp[i]);
		}
	}
	for (size_t i = 0; i < 3 && i < temp.getSize(); i++)
	{
		std::cout << i + 1 << ". " << temp[i].first->getName()
			<< " - " << temp[i].second << " sales" << std::endl;
	}
}
