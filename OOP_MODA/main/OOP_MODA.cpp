// OOP_MODA.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "System.h"
//#include <crtdbg.h>
int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	System& system = System::getInstance();
	system.run();
	return 0;
}

