#include "RequestRefund.h"

RequestRefund::RequestRefund(System& system) :Command(system) {}

void RequestRefund::execute()
{
	std::cout << "Enter reason for refund: ";
	char buffer[1024];
	std::cin.getline(buffer, sizeof(buffer));
	MyString reason(buffer);
	system.requestRefund(reason);
}
