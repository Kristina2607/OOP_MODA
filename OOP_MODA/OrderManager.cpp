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

unsigned OrderManager::getCounter() const
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

Order& OrderManager::getOrder(size_t index) const
{
    return getOrder(index);
}

