#include "RefundedOrders.h"

RefundedOrders::RefundedOrders(System& system):Command(system){}

void RefundedOrders::execute()
{
	system.refundedOrders();
}
