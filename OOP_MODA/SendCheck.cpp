#include "SendCheck.h"

SendCheck::SendCheck(System& system) :Command(system) {}

void SendCheck::execute()
{
	unsigned sum;
	std::cout << "Enter sum: ";
	std::cin >> sum;
	MyString code;
	std::cout << "Enter code: ";
	std::cin >> code;
	MyString clientEGN;
	std::cout << "Enter client's EGN: ";
	std::cin >> clientEGN;
	system.sendCheck(sum, code,clientEGN);
}
