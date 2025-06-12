#include "ItemsManager.h"

void ItemsManager::viewProduct(unsigned ID) const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i].getId() == ID)
		{
			items[i].printItem();
		}
	}
}

void ItemsManager::listProducts() const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
			items[i].printItem();
	}
}
