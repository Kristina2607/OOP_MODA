#include "ApproveRefund.h"

ApproveRefund::ApproveRefund(System& system) :Command(system){}

void ApproveRefund::execute()
{
	size_t index;
	std::cin >> index;
	system.approveRefund();

}
