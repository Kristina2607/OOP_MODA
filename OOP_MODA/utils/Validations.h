#pragma once
#include "MyString.h"
class Validations
{
public:
	static bool isValidEGN(const MyString& EGN) ;
	static bool isDigit(char ch);
	static bool containsOnlyDigits(const MyString& EGN);
	
};

