#include "Redeem.h"
#include "MyString.h"

Redeem::Redeem(System& system): Command(system) {}

void Redeem::execute()
{
	MyString code;
	std::cout << "Enter code: ";
	std::cin >> code;
	system.redeem(code);
}
