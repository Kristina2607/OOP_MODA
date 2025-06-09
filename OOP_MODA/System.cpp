#include "System.h"
#include "CommandFactory.h"

System& System::getInstance()
{
	static System instance;
	return instance;
}

void System::run()
{
	CommandFactory& commandFactory = CommandFactory::getInstance();

	while (true)
	{
		MyString text;
		std::cout << "> ";
		std::cin >> text;

		Command* command = commandFactory.getCommand(text);
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

void System::registerUser(User* newUser)
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	users.addObject(newUser);
}

void System::help()
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	loggedUser->help();
}

void System::viewProfile()
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	loggedUser->viewProfile();
}

void System::confirmOrder(size_t orderIndex) const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() != Role::Client)
	{
		throw std::logic_error("You cannot do this action");
	}

	Client* client = dynamic_cast<Client*>(loggedUser);
	if (client)
	{
		client->confirmOrder(orderIndex);
	}
}

void System::checkout() const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() == Role::Client)
	{
		Client* client = dynamic_cast<Client*>(loggedUser);
		if (client)
		{
			client->checkout();
		}
	}
}

void System::checkBalance() const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() == Role::Client)
	{
		Client* client = dynamic_cast<Client*>(loggedUser);
		if (client)
		{
			client->checkBalance();
		}
	}
}


