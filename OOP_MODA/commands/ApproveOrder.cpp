#include "ApproveOrder.h"

ApproveOrder::ApproveOrder(System& system): Command(system) {}

void ApproveOrder::execute()
{
	unsigned ID;
	std::cout << "Write the ID of the order: ";
	std::cin >> ID;
	system.approveOrder(ID);
}
