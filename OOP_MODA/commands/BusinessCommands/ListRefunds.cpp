#include "ListRefunds.h"

ListRefunds::ListRefunds(System& system):Command(system){}

void ListRefunds::execute()
{
	system.listRefunds();
}
