#include "ApproveOrder.h"

ApproveOrder::ApproveOrder(System& system): Command(system) {}

void ApproveOrder::execute()
{
	size_t index;
	std::cout << "Write the index of the order: ";
	std::cin >> index;
	system.approveOrder(index);
}
