#include "RejectOrder.h"

RejectOrder::RejectOrder(System& system): Command(system) {}

void RejectOrder::execute()
{
	size_t index;
	std::cout << "Write the index of the request: ";
	std::cin >> index;

	std::cout << "Write reason for rejection: ";
	char buffer[1024];
	std::cin.getline(buffer, sizeof(buffer));
	MyString reason(buffer);
	system.rejectOrder(index, reason);
}

