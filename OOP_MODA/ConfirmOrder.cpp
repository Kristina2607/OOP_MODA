#include "ConfirmOrder.h"

ConfirmOrder::ConfirmOrder(System& system): Command(system){}

void ConfirmOrder::execute()
{
	size_t index;
	std::cout << "Enter the index of the order: ";
	std::cin >> index;
	system.confirmOrder(index);
}
