#include "Item.h"

unsigned Item::nextID = 1;
Item::Item(): ID(0), name(""), price(0), rating(0), initialQuantity(0), availability(false) {}

Item::Item(const MyString& name, const MyString& description, double price, double rating, unsigned quantity, bool availability)
	:ID(nextID++), name(name), description(description), price(price), rating(rating), initialQuantity(quantity), currentQuantity(quantity), availability(availability) {}

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

unsigned Item::getInitialQuantity() const
{
	return initialQuantity;
}

unsigned Item::getCurrentQuantity() const
{
	return currentQuantity;
}

void Item::increaseQuantity(unsigned amount)
{
	currentQuantity += amount;
}

unsigned Item::getTotalSales() const
{
	return totalSales;
}

void Item::addSales(unsigned quantity)
{
	totalSales += quantity;
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
	std::cout << ID << " | "<< name << " | " << price << "BGN | " << rating << " stars |" << currentQuantity << " quantity" << std::endl;
}

void Item::serialize(std::ofstream& ofs) const
{
	ofs.write((const char*)(&ID), sizeof(unsigned));
	MyString::writeStringToFile(ofs, name);
	MyString::writeStringToFile(ofs, description);
	
	ofs.write((const char*)(&totalSales), sizeof(unsigned));
	ofs.write((const char*)(&price), sizeof(double));
	ofs.write((const char*)(&rating), sizeof(double));
	ofs.write((const char*)(&availability), sizeof(bool));
	ofs.write((const char*)(&initialQuantity), sizeof(unsigned));
	ofs.write((const char*)(&currentQuantity), sizeof(unsigned));
}

void Item::deserialize(std::ifstream& ifs)
{
	name = MyString::readStringFromFile(ifs);
	description = MyString::readStringFromFile(ifs);

	ifs.read((char*)(&totalSales), sizeof(unsigned));
	ifs.read((char*)(&price), sizeof(double));
	ifs.read((char*)(&rating), sizeof(double));
	ifs.read((char*)(&availability), sizeof(bool));
	ifs.read((char*)(&initialQuantity), sizeof(unsigned));
	ifs.read((char*)(&currentQuantity), sizeof(unsigned));
}
