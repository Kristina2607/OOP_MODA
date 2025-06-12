#include "Business.h"
#include "Order.h"
#include "Client.h"

Business& Business::getInstance()
{
    static Business instance;
    return instance;
}

void Business::viewProfile() const
{
    std::cout << "Business profile" << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "EGN: " << this->EGN << std::endl;
}

void Business::help() const
{
    std::cout << "You are allowed to:" << std::endl;

    std::cout << "> add item." << std::endl;
    std::cout << "> remove item." << std::endl;
    std::cout << "> view_revenue" << std:: endl;
    std::cout << "> approve_order" << std:: endl;
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
        if (items[i].getName() == name)
        {
            std::swap(items[i], items[items.getSize()]);
            std::cout << name << " is removed successffully." << std::endl;
        }
    }
    throw std::invalid_argument("Invalid name");
}

void Business::addItem(const MyString& name, double price, unsigned quantity, const MyString& description)
{
    Item newItem = Item(name, description, price, 0, quantity, 1);
    items.push_back(newItem);
    std::cout << name << " is added successffully."<< std::endl;
}

void Business::viewRevenue() const
{
    double revenue = 0;
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        revenue += orders[i].getTotalPrice();
    }
}

void Business::approveOrder(size_t index)
{
    if (index >= orders.getSize())
    {
        throw std::invalid_argument("Invalid index.");
    }
    orders[index].setStatus(Status::Shipped);
    std::cout << "Order #" << index <<" is approved and shipped. "<< std::endl;
}

void Business::rejectOrder(size_t index, const MyString& description)
{
    if (index >= orders.getSize())
    {
        throw std::invalid_argument("Invalid index.");
    }
    orders[index].getClient()->recieveRefund(orders[index].getTotalPrice());
    std::cout << "Order is rejected. Reason: " << description << std::endl;
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

    /*const Order* order = request.getOrder();
    for (size_t i = 0; i < orders->getProductsCount(); i++)
    {
        Item& product = orders->getProduct(i);
        unsigned quantity = order->getProductQuantity(i);
        product.increaseQuantity(quantity);
    }

    Client* client = request.getClient();
    client->getOrderManager().removeOrder(order->getID());*/

    request.getClient()->recieveRefund(request.getOrder()->getTotalPrice());
    refundRequests.erase(index);
    std::cout << "Refund is approved. The sum is returned to "<<request.getClient()->getName();
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
    orders.push_back(order);
}

void Business::listOrders() const
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        std::cout << (i + 1) << ".";
        orders[i].printOrder();
    }
}

void Business::listPendingOrders() const
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        if (orders[i].statusToString() == "Pending")
        {
            std::cout << (i + 1) << ".";
            orders[i].printOrder();
        }
    }
}

void Business::listBestSeliingProducts() const
{
    MyVector <MyPair<const Item*, unsigned>> temp;
    for (size_t i = 0; i < items.getSize(); i++)
    {
        unsigned initialQuantity = items[i].getInitialQuantity();
        unsigned currentQuantity = items[i].getCurrentQuantity();
        unsigned soldQuantity = initialQuantity - currentQuantity;
        if (soldQuantity > 0)  
        {
           MyPair<const Item*, unsigned> pair(&items[i], soldQuantity);
            temp.push_back(pair);
        }
    }
    for (size_t i = 0; i < temp.getSize(); i++)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < temp.getSize(); j++)
        {
            if (temp[i].second > temp[j].second)
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
