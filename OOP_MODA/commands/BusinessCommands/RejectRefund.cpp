#include "RejectRefund.h"

RejectRefund::RejectRefund(System& system) :Command(system) {}

void RejectRefund::execute()
{
	size_t index;
	std::cout << "Write the index of the request: ";
	std::cin >> index;
	std::cin.ignore();

	std::cout << "Write reason for rejection: ";
	char buffer[1024];
	std::cin.getline(buffer, sizeof(buffer));
	MyString reason(buffer);

	system.rejectRefund(index, reason);
}
