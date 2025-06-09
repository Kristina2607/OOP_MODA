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
