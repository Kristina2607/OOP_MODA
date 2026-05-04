#include "ListProducts.h"

ListProducts::ListProducts(System& system) :Command(system) {}

void ListProducts::execute()
{
	system.listProducts();
}
