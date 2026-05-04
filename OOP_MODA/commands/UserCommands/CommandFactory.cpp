#include "commands/UserCommands/CommandFactory.h"
#include "commands/SystemCommands/LoginCommand.h"
#include "commands/SystemCommands/RegisterCommand.h"
#include "commands/SystemCommands/HelpCommand.h"
#include "commands/SystemCommands/ViewProfile.h"
#include "commands/SystemCommands/InvalidCommand.h"
#include "commands/SystemCommands/LogoutCommand.h"
#include "commands/SystemCommands/SaveCommand.h"
#include "commands/SystemCommands/LoadCommand.h"

//Client
#include "commands/ClientCommands/ListProducts.h"
#include "commands/ClientCommands/ViewProduct.h"
#include "commands/ClientCommands/Redeem.h"
#include "commands/ClientCommands/AddToCart.h"
#include "commands/ClientCommands/RemoveFromCart.h"
#include "commands/ClientCommands/ApplyDiscount.h"
#include "commands/ClientCommands/RemoveDiscount.h"
#include "commands/ClientCommands/Checkout.h"
#include "commands/ClientCommands/CheckBalance.h"
#include "commands/ClientCommands/ViewCart.h"
#include "commands/ClientCommands/RequestRefund.h"
#include "commands/ClientCommands/ConfirmOrder.h"
#include "commands/ClientCommands/ListOrdersClient.h"
#include "commands/ClientCommands/OrderHistory.h"
#include "commands/ClientCommands/RateCommand.h"

//Business
#include "commands/BusinessCommands/ListOrders.h"
#include "commands/BusinessCommands/ListPendingOrders.h"
#include "commands/BusinessCommands/AddItem.h"
#include "commands/BusinessCommands/RemoveItem.h"
#include "commands/BusinessCommands/ListBestSellingProducts.h"
#include "commands/BusinessCommands/ApproveRefund.h"
#include "commands/BusinessCommands/RejectRefund.h"
#include "commands/BusinessCommands/ViewRevenue.h"
#include "commands/BusinessCommands/RejectOrder.h"
#include "commands/BusinessCommands/ApproveOrder.h"
#include "commands/BusinessCommands/ListRefunds.h"
#include "commands/BusinessCommands/RefundedOrders.h"

//Administrator
#include "commands/AdministratorCommands/CustomerInsignts.h"
#include "commands/AdministratorCommands/SendCheck.h"

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
		return new LoadCommand(System::getInstance());
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
	else if (text == "list-orders")
	{
		return new ListOrdersClient(System::getInstance());
	}
	else if (text == "order_history")
	{
		return new OrderHistory(System::getInstance());
	}
	else if (text == "rate")
	{
		return new RateCommand(System::getInstance());
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
