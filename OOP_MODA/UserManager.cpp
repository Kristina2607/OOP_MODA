#include "UserManager.h"

void UserManager::registerUser()
{
	MyString username;
	std::cout << "Enter username: " << std::endl;
	std::cin >> username;
	MyString password;
	std::cout << "Enter password: ";
	std::cin >> password;
	MyString EGN;
	std::cout << "Enter EGN: ";
	std::cin >> EGN;
	MyString role;
	std::cout << "Enter role (Client, Business, Administrator): ";
	std::cin >> role;
}
