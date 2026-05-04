#include "ListPendingOrders.h"

ListPendingOrders::ListPendingOrders(System& system) :Command(system) {}

void ListPendingOrders::execute()
{
	system.listPendingOrders();
}
