#include "Client.h"
#include "Order.h"
#include "Cart.h"

Client::Client(const MyString& name, const MyString& password, const MyString& EGN, Role role,
    double wallet, unsigned points, Cart cart) : User(name, password, EGN, role), wallet(wallet), points(points), cart(cart) { }

double Client::getWallet() const
{
    return wallet;
}

unsigned Client::getPoints() const
{
    return points;
}

MyString Client::getEGN() const
{
    return EGN;
}

unsigned Client::getOrdersCount() const
{
    return orders.getSize();
}

unsigned Client::getTotalSpent() const
{
    unsigned totalSpent = 0;
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        totalSpent += orders[i].getTotalPrice();
    }
    return totalSpent;
}

void Client::viewProfile() const
{
    std::cout << "Client" << std::endl;
    std::cout <<"Name: " << this->name << std::endl;
    std::cout << "Ponts: " << points << std::endl;
    std::cout << "Balance in your wallet: " << wallet << std::endl;
}

void Client::help() const
{
    std::cout << "You are allowed to:" << std::endl;
    std::cout << "> view_profile" << std::endl;
    std::cout << "> check_balance" << std::endl;
    std::cout << "> request_refund" << std::endl;

    std::cout << "> apply_discount" << std::endl;
    std::cout << "> remove_discount" << std::endl;

    std::cout << "> filter_by_rating" << std::endl;
    std::cout << "> filter_by_price (desc)" << std::endl;
    std::cout << "> filter_by_price (asc)" << std::endl;
    std::cout << "> filter_by_alphabetical_order" << std::endl;

    std::cout << "> add_to_cart" << std::endl;
    std::cout << "> remove_from_cart" << std::endl;
    std::cout << "> view_cart" << std::endl;
    std::cout << "> checkout" << std::endl;
}

User* Client::clone() const
{
    return new Client (*this);
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

void Client::redeemCheck(const Check& check)
{
    if (this->EGN == check.getEGN())
    {
        wallet += check.getSum();
    }
}

void Client::recieveRefund(double refund)
{
    wallet += refund;
}

void Client::refundedOrders() const
{
    for (size_t i = 0; i < orders.getSize(); i++)
    {
        if (orders[i].getIsRefunded() == 1)
        {
            orders[i].printOrder();
        }
    }
}

bool Client::requestRefund(const Business& business)
{
    if (!lastOrder)
    {
        throw std::logic_error("You can return only your last order. ");
    }
    bool approved = business.processRefundRequest(*lastOrder);
    if (approved)
    {
        wallet += lastOrder->getTotalPrice();
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
    if (index >= orders.getSize())
    {
        throw std::invalid_argument("Invalid argument");
    }
    else if (orders[index].statusToString() != "Shipped")
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
