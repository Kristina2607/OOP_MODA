#include "RemoveItem.h"

RemoveItem::RemoveItem(System& system) :Command(system) {}

void RemoveItem::execute()
{
	std::cout << "Enter name: ";
	char bufferName[1024];
	std::cin.getline(bufferName, sizeof(bufferName));
	MyString name(bufferName);

	system.removeItem(name);
}
