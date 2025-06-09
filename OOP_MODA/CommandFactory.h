#pragma once
#include "MyString.h"
#include "System.h"
#include "Command.h"

class CommandFactory
{
	CommandFactory() = default;

public:
	static CommandFactory& getInstance();
	CommandFactory(const CommandFactory& other) = delete;
	CommandFactory& operator=(const CommandFactory& other) = delete;

	Command* getCommand(const MyString& text);
};