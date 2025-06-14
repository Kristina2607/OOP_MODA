#pragma once
#include "MyString.h"

class Check
{
private:

	MyString code;
	unsigned sum;
	MyString clientEGN;
	bool isRedeemed;

public:
	Check() = default;
	Check(const MyString& code, unsigned sum, const MyString& clientEGN, bool isRedeemed);

	unsigned getSum() const;
	MyString getEGN() const;
	bool getIsRedeemed() const;

	bool isValidCode(const MyString& code);
	void redeem();

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
};

