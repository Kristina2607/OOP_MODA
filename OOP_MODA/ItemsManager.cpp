#include "ItemsManager.h"

void ItemsManager::viewProduct(unsigned ID) const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i].first.getId() == ID)
		{
			items[i].first.printItem();
		}
	}
}

void ItemsManager::listProducts() const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
			items[i].first.printItem();
	}
}
