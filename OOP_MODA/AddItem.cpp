#include "AddItem.h"

AddItem::AddItem(System& system) :Command(system){}

void AddItem::execute()
{
	MyString name;
	unsigned quantity;
	double price;

	char buffer[1024];
	std::cin.getline(buffer, sizeof(buffer));
	MyString description(buffer);

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
