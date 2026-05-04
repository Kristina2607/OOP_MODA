#include "AddItem.h"

AddItem::AddItem(System& system) :Command(system){}

void AddItem::execute()
{
	unsigned quantity;
	double price;

	std::cout << "Enter name: ";
	char bufferName[1024];
	std::cin.ignore();
	std::cin.getline(bufferName, sizeof(bufferName));
	MyString name(bufferName);

	std::cout << "Enter price: ";
	std::cin >> price;
	std::cout << "Enter quantity: ";
	std::cin >> quantity;

	std::cout << "Enter description: ";
	std::cin.ignore();
	char buffer[1024];
	std::cin.getline(buffer, sizeof(buffer));
	MyString description(buffer);

	system.addItem(name, price, quantity, description);
}
