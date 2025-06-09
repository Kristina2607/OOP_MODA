#include "System.h"
#include "CommandFactory.h"

void System::run()
{
	CommandFactory* commandFactory = new CommandFactory(*this);

	while (true) 
	{
		MyString text;
		std::cout << "> ";
		std::cin >> text;

		Command* command = commandFactory->getCommand(text);
		if (!command) {
			std::cout << "No such command exists!";
		}

		if (text == "exit")
		{
			break;
		}

		try 
		{
			command->execute();
		}
		catch (std::invalid_argument& ex) 
		{
			std::cout << ex.what() << std::endl;
		}
		catch (std::logic_error& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	delete commandFactory;
}

void System::list_products() const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		items[i].printItem();
	}
}

void System::view_product(unsigned ID) const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		if (items[i].getId() == ID)
		{
			items[i].printItem();
		}
	}
	throw std::invalid_argument("Invalid index.");
}

void System::login(const MyString& name, const MyString& pass)
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getName() == name && users[i]->checkPassword(pass))
		{
			loggedUser = users[i];
			return;
		}
	}
	throw std::invalid_argument("Invalid username or password!");
}

void System::registerUser(const MyString& name, const MyString& pass, const MyString& EGN)
{
	
}

void System::help()
{
	loggedUser->help();
}

void System::viewProfile()
{
	loggedUser->viewProfile();
}


