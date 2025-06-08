#include "Item.h"

unsigned Item::nextID = 1;
Item::Item(): ID(0), name(""), price(0), rating(0), quantity(0), availability(false) {}

Item::Item(const MyString& name, const MyString& description, double price, double rating, unsigned quantity, bool availability)
	:ID(nextID++), name(name), description(description), price(price), rating(rating), quantity(quantity), availability(availability) {}

unsigned Item::getId() const
{
	return ID;
}

MyString Item::getName() const
{
	return name;
}

MyString Item::getDescription() const
{
	return description;
}

double Item::getPrice() const
{
	return price;
}

unsigned Item::getRating() const
{
	return rating;
}

void Item::printItem() const
{
	std::cout << ID << " | "<< name << " | " << price << "BGN | " << rating << " stars |" << quantity << " quantity" << std::endl;
}
