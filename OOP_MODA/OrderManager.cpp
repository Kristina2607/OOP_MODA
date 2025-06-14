#include "OrderManager.h"

void OrderManager::removeID(size_t ID)
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

const Order& OrderManager::getLastOrder() const
{
    return orders.back();
}

void OrderManager::serialize(std::ofstream& ofs) const
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        orders[i].serialize(ofs);
    }
}

void OrderManager::deserialize(std::ifstream& ifs)
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        orders[i].deserialize(ifs);
    }
}

Order& OrderManager::getOrder(size_t index) const
{
    return getOrder(index);
}

Order& OrderManager::getOrder(size_t index)
{
    return getOrder(index);
}

