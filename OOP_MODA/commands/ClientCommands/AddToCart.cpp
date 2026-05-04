#include "AddToCart.h"

AddToCart::AddToCart(System& system) :Command(system) {}

void AddToCart::execute()
{
	unsigned ID;
	std::cout << "Enter ID: ";
    std::cin >> ID;

	unsigned quantity;
	std::cout << "Enter quatity: ";
	std::cin >> quantity;

	system.addToCart(ID, quantity);
}
