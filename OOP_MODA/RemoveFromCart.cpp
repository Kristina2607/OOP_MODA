#include "RemoveFromCart.h"

RemoveFromCart::RemoveFromCart(System& system) :Command(system) {}

void RemoveFromCart::execute()
{
	MyString name;
	std::cout << "Enter name: ";
	std::cin >> name;

	unsigned quantity;
	std::cout << "Enter quantity: ";
	std::cin >> quantity;

	system.removeFromCart(name, quantity);
}
