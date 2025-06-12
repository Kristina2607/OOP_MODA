#include "CommandFactory.h"
#include "LoginCommand.h"
#include "RegisterCommand.h"
#include "HelpCommand.h"
#include "ViewProfile.h"

//Client
#include "ListProducts.h"
#include "ViewProduct.h"
#include "Redeem.h"
#include "AddToCart.h"
#include "RemoveFromCart.h"
#include "ApplyDiscount.h"
#include "RemoveDiscount.h"
#include "Checkout.h"
#include "CheckBalance.h"
#include "viewCart.h"
#include "RefundedOrders.h"
#include "RequestRefund.h"

//Business
#include "ListOrders.h"
#include "ListPendingOrders.h"
#include "AddItem.h"
#include "RemoveItem.h"
#include "ListBestSellingProducts.h"
#include "ApproveRefund.h"
#include "RejectRefund.h"

//Administrator
#include "CustomerInsignts.h"
#include "SendCheck.h"

CommandFactory& CommandFactory::getInstance()
{
	static CommandFactory instance;
	return instance;
}


Command* CommandFactory::getCommand(const MyString& text)
{
	//All users:
	if (text == "login") 
	{
		return new LoginCommand(System::getInstance());
	}
	else if (text == "help")
	{
		return new HelpCommand(System::getInstance());
	}
	else if (text == "register")
	{
		return new RegisterCommand(System::getInstance());
	}
	else if (text == "view_profile")
	{
		return new ViewProfile(System::getInstance());
	}

	//Client:
	else if (text == "list_products")
	{
		return new ListProducts(System::getInstance());
	}
	else if (text == "view_product")
	{
		return new ViewProduct(System::getInstance());
	}
	else if (text == "redeem")
	{
		return new Redeem(System::getInstance());
	}
	else if (text == "add_to_cart")
	{
		return new AddToCart(System::getInstance());
	}
	else if (text == "remove_from_cart")
	{
		return new RemoveFromCart(System::getInstance());
	}
	else if (text == "apply_discount")
	{
		return new ApplyDiscount(System::getInstance());
	}
	else if (text == "remove_discount")
	{
		return new RemoveDiscount(System::getInstance());
	}
	else if (text == "checkout")
	{
		return new Checkout(System::getInstance());
	}
	else if (text == "check_balance")
	{
		return new CheckBalance(System::getInstance());
	}
	else if (text == "view_cart")
	{
		return new ViewCart(System::getInstance());
	}
	else if (text == "refunded_orders")
	{
		return new RefundedOrders(System::getInstance());
	}
	else if (text == "request_refund")
	{
		return new RequestRefund(System::getInstance());
	}


	//Business:
	else if (text == "list_orders")
	{
		return new ListOrders(System::getInstance());
	}
	else if (text == "list_pending_orders")
	{
		return new ListPendingOrders(System::getInstance());
	}
	else if (text == "add_item")
	{
		return new AddItem(System::getInstance());
	}
	else if (text == "remove_item")
	{
		return new RemoveItem(System::getInstance());
	}
	else if (text == "list_best_selling_products")
	{
		return new ListBestSellingProducts(System::getInstance());
	}
	else if (text == "approve_refund")
	{
		return new ApproveRefund(System::getInstance());
	}
	else if (text == "reject_refund")
	{
		return new RejectRefund(System::getInstance());
	}
	

	//Administrator:
	else if (text == "customers_insights")
	{
		return new CustomerInsignts(System::getInstance());
	}
	else if (text == "send_checks")
	{
		return new SendCheck(System::getInstance());
	}

	else
	{
		return nullptr;
	}
}
