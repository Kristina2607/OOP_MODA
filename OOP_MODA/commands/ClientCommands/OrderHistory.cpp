#include "OrderHistory.h"

OrderHistory::OrderHistory(System& system):Command(system){}

void OrderHistory::execute()
{
	system.orderHistory();
}
