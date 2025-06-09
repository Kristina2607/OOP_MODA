#include "System.h"
#include "CommandFactory.h"
#include "Client.h"
#include "Business.h"
#include "Administrator.h"

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

void System::listProducts() const
{
	for (size_t i = 0; i < items.getSize(); i++)
	{
		items[i].printItem();
	}
}

void System::viewProduct(unsigned ID) const
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

void System::logout()
{
	loggedUser = nullptr;
}

void System::help() const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	loggedUser->help();
}

void System::viewProfile() const
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
	if (loggedUser->getRole() != Role::Client)
	{
		throw std::logic_error("You cannot do this action");
	}

	Client* client = dynamic_cast<Client*>(loggedUser);
	if (client)
	{
		client->checkout();
	}
}

void System::redeem(const MyString& code) const
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
		client->redeemCheck(code);
	}
}

void System::checkBalance() const
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
		client->checkBalance();
	}
}

void System::applyDiscount() const
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
		client->applyDiscount();
	}
}

void System::removeDiscount() const
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
		client->removeDiscount();
	}
}

void System::addToCart(unsigned ID, unsigned quantity) const
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
		client->addToCart(ID, quantity);
	}
}

void System::removeFromCart(const MyString& name, unsigned quantity) const
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
		client->removeFromCart(name,quantity);
	}
}

void System::viewCart() const
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
		client->view_cart();
	}
}

void System::refundedOrders() const
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
		client->refundedOrders();
	}
}

void System::addItem(const MyString& name, double price, unsigned quantity, const MyString& description) const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() != Role::Business)
	{
		throw std::logic_error("You cannot do this action");
	}

	Business* business = dynamic_cast<Business*>(loggedUser);
	if (business)
	{
		business->addItem(name, price,quantity, description);
	}
}

void System::removeItem(const MyString& name) const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() != Role::Business)
	{
		throw std::logic_error("You cannot do this action");
	}

	Business* business = dynamic_cast<Business*>(loggedUser);
	if (business)
	{
		business->removeItem(name);
	}
}

void System::listPendingOrders() const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() != Role::Business)
	{
		throw std::logic_error("You cannot do this action");
	}

	Business* business = dynamic_cast<Business*>(loggedUser);
	if (business)
	{
		business->listPendingOrders();
	}
}

void System::listOrders() const
{

	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() != Role::Business)
	{
		throw std::logic_error("You cannot do this action");
	}

	Business* business = dynamic_cast<Business*>(loggedUser);
	if (business)
	{
		business->listOrders();
	}
}

void System::viewRevenue() const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() != Role::Business)
	{
		throw std::logic_error("You cannot do this action");
	}

	Business* business = dynamic_cast<Business*>(loggedUser);
	if (business)
	{
		business->viewRevenue();
	}
}


