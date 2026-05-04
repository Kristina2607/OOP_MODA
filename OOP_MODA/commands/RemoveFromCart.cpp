#include "RemoveFromCart.h"

RemoveFromCart::RemoveFromCart(System& system) :Command(system) {}

void RemoveFromCart::execute()
{
	std::cout << "Enter name: ";
	char bufferName[1024];
	std::cin.ignore();
	std::cin.getline(bufferName, sizeof(bufferName));
	MyString name(bufferName);

	unsigned quantity;
	std::cout << "Enter quantity: ";
	std::cin >> quantity;

	system.removeFromCart(name, quantity);
}
