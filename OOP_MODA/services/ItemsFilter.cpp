#include "ItemsFilter.h"

void FilterByRating::filter(MyVector<Item>& items)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; j < items.getSize(); j++)
		{
			if (items[j].getRating() > items[i].getRating())
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			std::swap(items[i], items[minIndex]);
		}
	}
}

void FilterByName::filter(MyVector<Item>& items)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; i < items.getSize(); j++)
		{
			if (items[j].getName() < items[minIndex].getName())
			{
				minIndex = j;
			}
		}
		if (i != minIndex)
		{
			std::swap(items[i], items[minIndex]);
		}
	}
}

FilterByPrice::FilterByPrice(bool ascending):ascending(ascending){}


void FilterByPrice::filter(MyVector<Item>& items)
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; j < items.getSize(); j++)
		{
			if (ascending ? (items[j].getPrice() < items[i].getPrice()) : (items[j].getPrice() > items[minIndex].getPrice()))
			{
				minIndex = j;
			}
		}
		if (i != minIndex)
		{
			std::swap(items[i], items[minIndex]);
		}
	}
}
