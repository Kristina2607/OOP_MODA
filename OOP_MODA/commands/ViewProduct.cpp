#include "ViewProduct.h"

ViewProduct::ViewProduct(System& system) :Command(system) {}

void ViewProduct::execute()
{
	unsigned ID;
	std::cout << "Enter the index of the product: ";
	std::cin >> ID;
	system.viewProduct(ID);
}
