#include "AddItem.h"

AddItem::AddItem(System& system) :Command(system){}

void AddItem::execute()
{
	MyString name;
	MyString description;
	unsigned quantity;
	double price;

	std::cout << "Enter name: ";
	std::cin >> name;
	std::cout << "Enter price: ";
	std::cin >> price;
	std::cout << "Enter quantity: ";
	std::cin >> quantity;
	std::cout << "Enter description: ";
	std::cin >> description;

	system.addItem(name, price, quantity, description);
}
