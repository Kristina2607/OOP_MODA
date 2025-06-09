#pragma once
#include "MyString.h"
#include "System.h"
#include "Command.h"

class CommandFactory
{
	System& system;

public:
	CommandFactory(System& system);
	Command* getCommand(const MyString& text);
};