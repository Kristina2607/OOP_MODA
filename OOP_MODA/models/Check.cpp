#include "Check.h"

Check::Check(const MyString& code, unsigned sum, const MyString& clientEGN, bool isRedeemed) 
	: code(code), sum(sum), clientEGN(clientEGN), isRedeemed(false) {}

unsigned Check::getSum() const
{
	return sum;
}

MyString Check::getEGN() const
{
	return clientEGN;
}

bool Check::getIsRedeemed() const
{
	return isRedeemed;
}

bool Check::isValidCode(const MyString& code)
{
	if (this->code == code)
	{
		return true;
	}
	return false;
}

void Check::redeem()
{
	if (isRedeemed)
	{
		throw std::runtime_error("Check already redeemed!");
	}
	isRedeemed = true;
}

void Check::serialize(std::ofstream& ofs) const
{
	MyString::writeStringToFile(ofs, code);
	ofs.write((const char*)&sum, sizeof(unsigned));
	MyString::writeStringToFile(ofs, clientEGN);
	ofs.write((const char*)&isRedeemed, sizeof(bool));
}

void Check::deserialize(std::ifstream& ifs)
{
	code = MyString::readStringFromFile(ifs);
	ifs.read((char*)&sum, sizeof(unsigned));
	clientEGN = MyString::readStringFromFile(ifs);
	ifs.read((char*)&isRedeemed, sizeof(bool));
}
