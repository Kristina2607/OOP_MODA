#include "ListOrders.h"

ListOrders::ListOrders(System& system) :Command(system) {}

void ListOrders::execute()
{
	system.listOrders();
}
