#include "RegisterCommand.h"
#include "Role.h"

RegisterCommand::RegisterCommand(System& system) :Command(system) {}

void RegisterCommand::execute()
{
	MyString name;
	std::cout << "Name:";
	std::cin >> name;

	MyString password;
	std::cout << "Password";
	std::cin >> password;

	MyString EGN;
	std::cout << "EGN:";
	std::cin >> EGN;

	Role role;
	std::cout << "Select role (Administrator, Business, Client): ";
	//std::cin >> role;
}
