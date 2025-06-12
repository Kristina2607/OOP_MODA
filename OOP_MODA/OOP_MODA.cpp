// OOP_MODA.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "System.h"

int main()
{
	System& system = System::getInstance();
	system.run();
	return 0;
}

