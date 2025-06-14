#include "CommandFactory.h"
#include "LoginCommand.h"
#include "RegisterCommand.h"
#include "HelpCommand.h"
#include "ViewProfile.h"
#include "InvalidCommand.h"
#include "LogoutCommand.h"
#include "SaveCommand.h"

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
#include "ViewCart.h"
#include "RefundedOrders.h"
#include "RequestRefund.h"
#include "ConfirmOrder.h"

//Business
#include "ListOrders.h"
#include "ListPendingOrders.h"
#include "AddItem.h"
#include "RemoveItem.h"
#include "ListBestSellingProducts.h"
#include "ApproveRefund.h"
#include "RejectRefund.h"
#include "ViewRevenue.h"
#include "RejectOrder.h"
#include "ApproveOrder.h"
#include "ListRefunds.h"

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
	else if (text == "logout")
	{
		return new LogoutCommand(System::getInstance());
	}
	else if (text == "save")
	{
		return new SaveCommand(System::getInstance());
	}
	else if (text == "load")
	{
		return new SaveCommand(System::getInstance());
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
	else if (text == "confirm_order")
	{
		return new ConfirmOrder(System::getInstance());
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
	else if (text == "list_refunds")
	{
		return new ListRefunds(System::getInstance());
	}
	else if (text == "approve_refund")
	{
		return new ApproveRefund(System::getInstance());
	}
	else if (text == "reject_refund")
	{
		return new RejectRefund(System::getInstance());
	}
	else if (text == "view_revenue")
	{
		return new ViewRevenue(System::getInstance());
	}
	else if (text == "reject_order")
	{
		return new RejectOrder(System::getInstance());
    }
	else if (text == "approve_order")
	{
		return new ApproveOrder(System::getInstance());
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
		return new InvalidCommand(System::getInstance());
	}
}
