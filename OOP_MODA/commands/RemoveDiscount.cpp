#include "RemoveDiscount.h"

RemoveDiscount::RemoveDiscount(System& system) :Command(system){}

void RemoveDiscount::execute()
{
	system.removeDiscount();
}
