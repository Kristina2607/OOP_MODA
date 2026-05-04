#include "RegisterCommand.h"
#include "Role.h"
#include"Validations.h"

RegisterCommand::RegisterCommand(System& system) :Command(system) {}

void RegisterCommand::execute()
{
	MyString name;
	std::cout << "Name:";
	std::cin >> name;

	MyString password;
	std::cout << "Password: ";
	std::cin >> password;

	MyString EGN;
	std::cout << "EGN: ";
	std::cin >> EGN;
	if (!Validations::isValidEGN(EGN))
	{
		throw std::invalid_argument("Invalid EGN.");
	}
	std::cout << "Select role (1.Administrator, 2.Business, 3.Client): ";

	MyString roleInput;
	std::cin >> roleInput;

	Role role;
	if (roleInput == "Administrator")
	{
		role = Role::Admin;
	}
	else if (roleInput == "Business") 
	{
		role = Role::Business;
	}
	else if (roleInput == "Client")
	{
		role = Role::Client;
	}
	else 
	{
		throw std::invalid_argument("Invalid role");
	}

	system.registerUser(name, password, EGN, role);
}
