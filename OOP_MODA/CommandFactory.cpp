#include "CommandFactory.h"
#include "LoginCommand.h"
#include "RegisterCommand.h"
#include "HelpCommand.h"
#include "ListProducts.h"
#include "ViewProfile.h"
#include "ViewProduct.h"

CommandFactory& CommandFactory::getInstance()
{
	static CommandFactory instance;
	return instance;
}


Command* CommandFactory::getCommand(const MyString& text)
{
	if (text == "login") 
	{
		return new LoginCommand(System::getInstance());
	}
	if (text == "help")
	{
		return new HelpCommand(System::getInstance());
	}
	if (text == "register")
	{
		return new RegisterCommand(System::getInstance());
	}
	if (text == "list_product")
	{
		return new ListProducts(System::getInstance());
	}
	if (text == "view_profile")
	{
		return new ViewProfile(System::getInstance());
	}
	if (text == "view_product")
	{
		return new ViewProduct(System::getInstance());
	}
	else
	{
		return nullptr;
	}
}
