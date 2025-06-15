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

size_t ItemsManager::getSize() const
{
	return items.getSize();
}

void ItemsManager::addItem(const Item& obj)
{
	items.push_back(obj);
}

void ItemsManager::erase(size_t index)
{
	items.erase(index);
}

bool ItemsManager::isAvailable(unsigned ID)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i].getId() == ID)
		{
			return true;
		}
	}
	return false;
}

const Item* ItemsManager::findByID(unsigned ID)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i].getId() == ID)
		{
			return &items[i];
		}
	}
	return nullptr;
}

Item& ItemsManager::getItem(size_t index)
{
	return items[index];
}

const Item& ItemsManager::getItem(size_t index) const
{
	return items[index];
}

const Item& ItemsManager::getLastItem() const
{
	return items.back();
}

void ItemsManager::serialize(std::ofstream& ofs) const
{
	size_t itemsCount = items.getSize();
	ofs.write((const char*)&itemsCount, sizeof(itemsCount));
	for (size_t i = 0; i < items.getSize(); i++)
	{
		items[i].serialize(ofs);
	}
}

void ItemsManager::deserialize(std::ifstream& ifs)
{
	size_t itemsCount = 0;
	ifs.read((char*)&itemsCount, sizeof(itemsCount));
	for (size_t i = 0; i < itemsCount; i++)
	{
		Item item;
		item.deserialize(ifs);
		items.push_back(item);
	}
}
