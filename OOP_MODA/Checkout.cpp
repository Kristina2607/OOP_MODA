#include "Checkout.h"

Checkout::Checkout(System& system):Command(system){}

void Checkout::execute()
{
	system.checkout();
}
