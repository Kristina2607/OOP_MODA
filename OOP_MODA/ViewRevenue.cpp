#include "ViewRevenue.h"

ViewRevenue::ViewRevenue(System& system) :Command(system) { }

void ViewRevenue::execute()
{
	system.viewRevenue();
}
