#include "Order.h"
#include "Client.h"

unsigned Order::NextOrderID = 1;

Order::Order(MyVector<MyPair<Item, unsigned>> items, Client* client, double totalPrice, unsigned points, Status status)
    : ID(NextOrderID++), items(items), client(client), totalPrice(totalPrice), points(points), status(status) {}

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

Client* Order::getClient() const
{
    return client;
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

bool Order::hasUsedDiscount() const
{
    return usedDiscount;
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
            std::cout << items[i].second << "x" << items[i].first.getName() << ",";
        }
        std::cout << " - ";
    }
    std::cout << totalPrice << " BGN";
    std::cout << " - " << statusToString() << std::endl;
}


