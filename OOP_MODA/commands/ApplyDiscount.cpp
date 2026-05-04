#include "ApplyDiscount.h"

ApplyDiscount::ApplyDiscount(System& system) :Command(system) {}

void ApplyDiscount::execute()
{
	system.applyDiscount();
}
