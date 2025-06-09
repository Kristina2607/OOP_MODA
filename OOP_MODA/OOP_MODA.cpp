// OOP_MODA.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "Client.h"
#include "Business.h"
#include "Order.h"
#include "Cart.h";
#include "Item.h"
#include "RefundRequest.h"

int main()
{
	Business& business1 = Business::getInstance();

	Item item1("palto", "kojeno", 23, 3, 5, 1);
	Item item2;

	

	business1.addItem("palto", 23, 2, "kojeno");
	business1.viewRevenue();
	business1.removeItem("palto");

	
	return 0;
}

