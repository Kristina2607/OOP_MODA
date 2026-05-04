#include "OrderManager.h"

void OrderManager::removeID(unsigned ID)
{
        for (size_t i = 0; i < orders.getSize(); i++)
        {
            if (orders[i].getID() == ID)
            {
                orders.erase(i);
                break;
            }
        }
}

void OrderManager::addOrder(const Order& newOrder)
{
    orders.push_back(newOrder);
}

void OrderManager::removeOrder(size_t index)
{
    orders.erase(index);
}

unsigned OrderManager::getSize() const
{
    return orders.getSize();
}

unsigned OrderManager::getTotalSpent() const
{
        unsigned totalSpent = 0;
        for (size_t i = 0; i < orders.getSize(); i++)
        {
            totalSpent += orders[i].getTotalPrice();
        }
        return totalSpent;
}

void OrderManager::refundedOrders() const
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        if (orders[i].getIsRefunded() == 1)
        {
            orders[i].printOrder();
        }
    }
}

bool OrderManager::isEmpty()
{
   return orders.empty();
}

Order& OrderManager::getLastOrder() 
{
    if (orders.empty())
    {
        throw std::logic_error("There are no orders.");
    }
    return orders[orders.getSize() - 1];
}

const MyVector<Order>& OrderManager::getOrders() const
{
    return orders;
}

void OrderManager::serialize(std::ofstream& ofs) const
{
    size_t ordersSize = orders.getSize();
    ofs.write((const char*)&ordersSize, sizeof(ordersSize));
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        orders[i].serialize(ofs);
    }
}

void OrderManager::deserialize(std::ifstream& ifs)
{
    size_t ordersSize = 0;
    ifs.read((char*)&ordersSize, sizeof(ordersSize));
    for (size_t i = 0; i < ordersSize; i++)
    {
        Order order;
        order.deserialize(ifs);
        orders.push_back(order);
    }
}

const Order& OrderManager::getOrder(size_t index) const
{
    return orders[index];
}

Order& OrderManager::getOrder(size_t index)
{
    return orders[index];
}

Order* OrderManager::getOrderById(unsigned ID)
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        if (orders[i].getID() == ID) {
            return &orders[i];
        }
    }
    return nullptr;
}

