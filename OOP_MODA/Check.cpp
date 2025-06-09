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

void Check::redeem()
{
	isRedeemed = true;
}
