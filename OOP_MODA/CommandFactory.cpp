#include "CommandFactory.h"
#include "LoginCommand.h"
#include "RegisterCommand.h"
#include "HelpCommand.h"

CommandFactory::CommandFactory(System& system) : system(system) {}

Command* CommandFactory::getCommand(const MyString& text)
{
	if (text == "login") 
	{
		return new LoginCommand(system);
	}
	if (text == "help")
	{
		return new HelpCommand(system);
	}
	if (text == "register")
	{
		return new RegisterCommand(system);
	}
	else
	{
		return nullptr;
	}
}
