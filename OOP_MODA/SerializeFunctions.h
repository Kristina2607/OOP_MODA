#pragma once
#include "OrderManager.h"
#include "ItemsManager.h"
#include "User.h"
#include "HeterogeneousContainer.hpp"

class SerializeFunctions
{
private:
	static HeterogeneousContainer<User> users;
	static OrderManager* orderMnager;	
	static ItemsManager* orderManager;

	static size_t getFileSize(std::ifstream& ifs);
	static void writeStringToFile(std::ofstream& ofs, const MyString& str);
	static MyString readStringFromFile(std::ifstream& ifs);


	static void loadUsersFromFile();
	static void loadOrdersFromFile();


	static void saveUsersToFile();
	static void saveOrdersFromFile();

public:
	static void saveSystemToFile();
	static void loadSystemFromFile();

};

