#include "RemoveItem.h"

RemoveItem::RemoveItem(System& system) :Command(system) {}

void RemoveItem::execute()
{
	MyString name;
	std::cout << "Enter name: ";
	std::cin >> name;
	system.removeItem(name);
}
