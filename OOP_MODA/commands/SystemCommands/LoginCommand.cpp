#include "LoginCommand.h"
LoginCommand::LoginCommand(System& system) : Command(system) {}

void LoginCommand::execute()
{
	MyString name;
	std::cout << "Name: ";
	std::cin >> name;

	MyString pass;
	std::cout << "Password: ";
	std::cin >> pass;

	system.login(name, pass);
}
