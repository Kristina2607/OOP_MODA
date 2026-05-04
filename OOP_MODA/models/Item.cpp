#include "Item.h"

unsigned Item::nextID = 1;
Item::Item(): ID(0), name(""), price(0), totalRating(0), initialQuantity(0), isAvailable(false) {}

Item::Item(const MyString& name, const MyString& description, double price, unsigned totalRating, unsigned numberOfRatings, unsigned quantity, bool availability)
	:ID(nextID++), name(name), description(description), price(price), totalRating(totalRating), numberOfRatings(numberOfRatings), initialQuantity(quantity), currentQuantity(quantity), isAvailable(availability) {}

unsigned Item::getID() const
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

void Item::decreaseQuantity(unsigned amount)
{
	currentQuantity -= amount;
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
	return totalRating;
}

void Item::printItem() const
{
	std::cout << ID << " | "<< name << " | " << price << "BGN | " << getAverageRating() << " stars |" << currentQuantity << " quantity" << std::endl;
}

void Item::addRating(unsigned stars)
{
	numberOfRatings++;
	totalRating += stars;
}

void Item::removeRating(unsigned stars)
{
	if (numberOfRatings == 0)
	{
		return;
	}
	totalRating -= stars;
	numberOfRatings--;
}

double Item::getAverageRating() const
{
	if (numberOfRatings == 0)
	{
		return 0;
	}
	return static_cast<double>(totalRating) / numberOfRatings;
}

void Item::serialize(std::ofstream& ofs) const
{
	ofs.write((const char*)(&ID), sizeof(unsigned));
	MyString::writeStringToFile(ofs, name);
	MyString::writeStringToFile(ofs, description);
	
	ofs.write((const char*)(&totalSales), sizeof(unsigned));
	ofs.write((const char*)(&price), sizeof(double));
	ofs.write((const char*)(&totalRating), sizeof(double));
	ofs.write((const char*)(&numberOfRatings), sizeof(unsigned));
	ofs.write((const char*)(&isAvailable), sizeof(bool));
	ofs.write((const char*)(&initialQuantity), sizeof(unsigned));
	ofs.write((const char*)(&currentQuantity), sizeof(unsigned));
}

void Item::deserialize(std::ifstream& ifs)
{
	ifs.read((char*)(&ID), sizeof(unsigned));
	name = MyString::readStringFromFile(ifs);
	description = MyString::readStringFromFile(ifs);

	ifs.read((char*)(&totalSales), sizeof(unsigned));
	ifs.read((char*)(&price), sizeof(double));
	ifs.read((char*)(&totalRating), sizeof(double));
	ifs.read((char*)(&numberOfRatings), sizeof(unsigned));
	ifs.read((char*)(&isAvailable), sizeof(bool));
	ifs.read((char*)(&initialQuantity), sizeof(unsigned));
	ifs.read((char*)(&currentQuantity), sizeof(unsigned));
}
