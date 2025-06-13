#include "Client.h"
#include "Order.h"
#include "Cart.h"
#include "Role.h"

Client::Client() : User(Role::Client)
{}

Client::Client(const MyString& name, const MyString& password, const MyString& EGN)
    :User(name, password, EGN, Role::Client) {}

Client::Client(const MyString& name, const MyString& password, const MyString& EGN,
    double wallet, unsigned points, Cart cart) : User(name, password, EGN, Role::Client), wallet(wallet), points(points), cart(cart) { }

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

OrderManager Client::getOrderManger() const
{
    return orders;
}

unsigned Client::getOrdersCount() const
{
    return orders.getCounter();
}

unsigned Client::getTotalSpent() const
{
    return orders.getTotalSpent();
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
    std::cout<<std::endl;
    std::cout << "You are allowed to:" << std::endl;
   
    std::cout << "> check_balance" << std::endl;
    std::cout << "> request_refund" << std::endl;
    std::cout << "> redeem" << std::endl;

    std::cout << "> list_products" << std::endl;
    std::cout << "> list_orders" << std::endl;
    std::cout << "> order_history" << std::endl;
    std::cout << "> refunded_orders" << std::endl;

    std::cout << "> view_product " << std::endl;
    std::cout << "> apply_discount" << std::endl;
    std::cout << "> remove_discount" << std::endl;
    std::cout << "> confirm_order" << std::endl;
    std::cout << "> rate" << std::endl;
    std::cout << "> request_refund" << std::endl;

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

void Client::viewCart() const
{
    cart.view_cart();
}

void Client::clearCart()
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

void Client::redeemCheck(const MyString& code)
{
    Check targetCheck;

    for (size_t i = 0;i<recievedChecks.getSize();i++)
    {
        if (recievedChecks[i].isValidCode(code) && !recievedChecks[i].getIsRedeemed()) {
            targetCheck = recievedChecks[i];
            break;
        }
    }
    throw std::runtime_error("No valid check found with this code!");

    targetCheck.redeem();
    wallet += targetCheck.getSum();

    std::cout << "Successfully redeemed check for " << targetCheck.getSum()
        << " BGN. New balance: " << wallet << " BGN\n";
}

void Client::recieveCheck(const Check& check)
{
    if (check.getEGN() != this->getEGN())
    {
        throw std::runtime_error("Check recipient EGN doesn't match!");
    }
    recievedChecks.push_back(check);
}

void Client::recieveRefund(double refund)
{
    wallet += refund;
}

void Client::refundedOrders() const
{
    orders.refundedOrders();
}

RefundRequest* Client::requestRefund(const MyString& reason) 
{
    if (orders.isEmpty())
    {
        throw std::logic_error("There are no orders. ");
    }
    const Order& lastOrder = orders.getLastOrder();
    if (lastOrder.statusToString() != "Delivered") 
    {
        throw std::logic_error("This order is not delivered yet.");
    }

    RefundRequest* request = new RefundRequest(reason, &lastOrder, const_cast<Client*>(this));
    this->points = 0;
    std::cout << "Refund request submitted for last order (" << lastOrder.getTotalPrice() << 
        " BGN). All loyalty points have been removed." << std::endl;

    return request;
}

Order& Client::checkout()
{
    double totalPrice = cart.getTotalPrice();
    if (wallet < totalPrice)
    {
        throw std::logic_error("Not enougn money in the wallet.");
    }
    wallet -= totalPrice;
    Order newOrder = cart.toOrder();
    orders.addOrder(newOrder);
    cart.clear_cart();

    std::cout << "Your order is placed successfully! Now is waiting for confirmation." << std::endl;
   
    return newOrder;
}

void Client::rateOrder(unsigned ProductID, unsigned rating)
{

}

void Client::confirmOrder(size_t index)
{
    if (index >= orders.getCounter())
    {
        throw std::invalid_argument("Invalid argument");
    }
    else if (orders.getOrder(index).statusToString() != "Shipped")
    {
        throw std::logic_error("This order is not shipped yet.");
    }
    orders.getOrder(index).setStatus(Status::Delivered);
    unsigned earnedPoints = orders.getOrder(index).getTotalPrice() * 5;
    points += earnedPoints;
    std::cout << "Order confirmed as received. You earned " << earnedPoints << " points." << std::endl;
}

void Client::listOrders() const
{
    for (size_t i = 0; i < orders.getCounter(); i++)
    {
        if (orders.getOrder(i).statusToString() == "Shipped")
        {
            orders.getOrder(i).printOrder();
        }
    }
}

void Client::orderHistory() const
{
    for (size_t i = 0; i < orders.getCounter(); i++)
    {
        if (orders.getOrder(i).statusToString() == "Delivered")
        {
            orders.getOrder(i).printOrder();
        }
    }
}

void Client::listProducts() const
{
    catalog.listProducts();
}

void Client::viewProduct(unsigned ID) const
{
    catalog.viewProduct(ID);
}
