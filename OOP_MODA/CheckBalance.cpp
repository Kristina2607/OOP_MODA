#include "CheckBalance.h"

CheckBalance::CheckBalance(System& system) :Command(system) {}

void CheckBalance::execute()
{
	system.checkBalance();
}
