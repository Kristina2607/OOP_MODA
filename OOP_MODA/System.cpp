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

Business* System::getBusiness() const
{
	if (!business)
	{
		throw std::logic_error("Business profile not initialized");
	}
	return business;
}

Administrator* System::getAdministrator() const
{
	if (!admin)
	{
		throw std::logic_error("Administrator profile not initialized.");
	}
	return admin;
}

void System::sendCheck(unsigned sum, const MyString& code, const MyString& clientEGN) const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() != Role::Admin)
	{
		throw std::logic_error("You cannot do this action");
	}

	Administrator* admin = dynamic_cast<Administrator*>(loggedUser);
	if (admin)
	{
		admin->sendChecks(sum, code, clientEGN);
	}
}

void System::customerInsights() const
{
	if (!loggedUser)
	{
		throw std::logic_error("No user logged in.");
	}
	if (loggedUser->getRole() != Role::Admin)
	{
		throw std::logic_error("You cannot do this action");
	}

	Administrator* admin = dynamic_cast<Administrator*>(loggedUser);
	if (admin)
	{
		admin->customerInsights();
	}
}

System::~System()
{
	delete business;
	delete admin;
	delete loggedUser;
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

void System::login(const MyString& name, const MyString& pass)
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getName() == name && users[i]->checkPassword(pass))
		{
			if (users[i]->getRole() == Role::Admin)
			{
				loggedUser = admin;
				return;
			}
			else if (users[i]->getRole() == Role::Business)
			{
				loggedUser = business;
				return;
			}
			loggedUser = users[i];
			std::cout << "Login successful! Welcome, " << users[i]->getName() << std::endl;
			return;
		}
	}
	throw std::invalid_argument("Invalid username or password!");
}

void System::registerUser(const MyString& name, const MyString& password, const MyString& EGN, Role role)
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getName() == name)
		{
			throw std::invalid_argument("User with this EGN already exists");
		}
	}
	User* newUser = nullptr;
	switch (role)
	{
	case Role::Client:
	{
		newUser = new Client(name, password, EGN);
		users.addObject(newUser);

		break;
	}
	case Role::Business:
	{
		if (business)
		{
			throw std::logic_error("Business already exists!");
		}
		business = new Business(name, password, EGN);
		loggedUser = business;
		break;
	}
	case Role::Admin:
	{
		if (admin)
		{
			throw std::logic_error("Admin already exists!");
		}
		admin = new Administrator(name, password, EGN);
		loggedUser = admin;
		break;
	}
	default:
		throw std::invalid_argument("Invalid role");
	}

	std::cout << "Registration successful!" << std::endl;
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

void System::confirmOrder(size_t orderIndex)
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

void System::listProducts() const
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
		client->listProducts();
	}
}

void System::viewProduct(unsigned ID) const
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
		client->viewProduct(ID);
	}
}

void System::checkout()
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
		Order& newOrder = client->checkout();
		business->recieveOrderRequest(newOrder);
	}
}

void System::redeem(const MyString& code)
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

void System::applyDiscount()
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

void System::removeDiscount()
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

void System::addToCart(unsigned ID, unsigned quantity)
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

void System::removeFromCart(const MyString& name, unsigned quantity)
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
		client->removeFromCart(name, quantity);
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
		client->viewCart();
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

void System::requestRefund(Business* business, const MyString& reason)
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
		RefundRequest* request = client->requestRefund(reason);
		business->recieveRefundRequest(request);
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
		business->addItem(name, price, quantity, description);
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

void System::approveRefund(size_t index)
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
		business->approveRefund(index);
	}
}

void System::rejectRefund(size_t index, const MyString& reason)
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
		business->rejectRefund(index, reason);
	}
}

void System::listBestSellingProducts() const
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
		business->listBestSeliingProducts();
	}
}


