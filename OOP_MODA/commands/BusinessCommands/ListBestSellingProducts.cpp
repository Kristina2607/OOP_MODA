#include "ListBestSellingProducts.h"

ListBestSellingProducts::ListBestSellingProducts(System& system) :Command(system) {}

void ListBestSellingProducts::execute()
{
	system.listBestSellingProducts();
}
