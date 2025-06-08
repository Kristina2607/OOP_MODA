#include "Client.h"

Client::Client(double wallet, unsigned points, Cart cart) :wallet(wallet), points(points), cart(cart) { }

double Client::getWallet() const
{
    return wallet;
}

unsigned Client::getPoints() const
{
    return points;
}

void Client::view_profile() const
{
    std::cout << "Client" << std::endl;
    std::cout <<"Name: " << this->name << std::endl;
    std::cout << "Ponts: " << points << std::endl;
    std::cout << "Balance in your wallet: " << wallet << std::endl;
}

void Client::help() const
{
    std::cout << "You are allowed to:" << std::endl;
    std::cout << "~view_profile." << std::endl;
    std::cout << "~check_balance." << std::endl;
    std::cout << "~request_refund." << std::endl;
    std::cout << "~apply_discount" << std::endl;
    std::cout << "~remove_discount." << std::endl;
}

User* Client::clone() const
{
    return new Client (*this);
}

MyString Client::getRole() const
{
    return "Client";
}

bool Client::hasPermission(const MyString& action) const
{
    return User::hasPermission(action);
}

void Client::addToCart(unsigned ID, unsigned quantity)
{
    cart.addToCart(ID, quantity);
}

void Client::removeFromCart(const MyString& name, unsigned quantity)
{
    cart.removeFromCart(name, quantity);
}

void Client::view_cart() const
{
    cart.view_cart();
}

void Client::clear_cart()
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
    std::cout <<"Current balance: " << wallet << " BGN" << std::endl;
    std::cout << "Loyalty points: " << points << std::endl;
}

void Client::recieveRefund(double refund)
{
    wallet += refund;
}

void Client::refunded_orders() const
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        if (orders[i].getIsRefunded() == 1)
        {
            orders[i].printOrder();
        }
    }
}

bool Client::request_refund(const Business& business)
{
    if (!lastOrder)
    {
        throw std::logic_error("You can return only your last order. ");
    }
    bool approved = business.processRefundRequest(*lastOrder);
    if (approved)
    {
        wallet += lastOrder->getTotalPrice();
        //to4ki?
        orders.pop_back();
        lastOrder = orders.empty() ? nullptr : &orders.back();
        return true;
    }
    return false;
}

void Client::checkout()
{
    double totalPrice = cart.getTotalPrice();
    if (wallet < totalPrice)
    {
        throw std::logic_error("Not enougn money in the wallet.");
    }
    wallet -= totalPrice;
    Order newOrder = cart.toOrder();
    orders.push_back(newOrder);
    std::cout << "Your order is placed successfully! Now is waiting for confirmation." << std::endl;
    cart.clear_cart();
}

void Client::confirmOrder(size_t index)
{
    //validira se indeksa
    if (orders[index].statusToString() != "Shipped")
    {
        throw std::logic_error("This order is not shipped yet.");
    }
    orders[index].setStatus(Status::Delivered);
    unsigned earnedPoints = orders[index].getTotalPrice() * 5;
    points += earnedPoints;
    std::cout << "Order confirmed as received. You earned " << earnedPoints << " points." << std::endl;
}

void Client::list_orders() const
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        if (orders[i].statusToString() == "Shipped")
        {
            orders[i].printOrder();
        }
    }
}

void Client::order_history() const
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        if (orders[i].statusToString() == "Delivered")
        {
            orders[i].printOrder();
        }
    }
}
