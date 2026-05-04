#include "CustomerInsignts.h"

CustomerInsignts::CustomerInsignts(System& system) :Command(system){}

void CustomerInsignts::execute()
{
	system.customerInsights();
}
