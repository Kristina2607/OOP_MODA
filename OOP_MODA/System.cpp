#include "System.h"

void System::list_products() const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		items[i].printItem();
	}
}

void System::view_product(unsigned ID) const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i].getId() == ID)
		{
			items[i].printItem();
		}
	}
	throw std::invalid_argument("Invalid index.");
}
