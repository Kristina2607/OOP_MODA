#include "System.h"
#include "CommandFactory.h"
#include "Client.h"
#include "Business.h"
#include "Administrator.h"
#include "StreamUtils.h"

System::System()
{
	loadSystem();
}

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

void System::sendCheck(unsigned sum, const MyString& code, const MyString& clientEGN)
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
		Client* client = nullptr;
		for (size_t i = 0; i < clients.getSize(); i++)
		{
			if (clients[i].getEGN() == clientEGN)
			{
				client = &clients[i];
				break;
			}
		}
		admin->sendChecks(sum, code, *client);
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
		if (!command)
		{
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
		catch (std::runtime_error& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}

void System::login(const MyString& name, const MyString& pass)
{
	if (admin && admin->checkLogData(name, pass))
	{
		loggedUser = admin;
		std::cout << "Login successful! Welcome, " << admin->getName() << std::endl;
		return;
	}
	else if (business && business->checkLogData(name, pass))
	{
		loggedUser = business;
		std::cout << "Login successful! Welcome, " << business->getName() << std::endl;
		return;
	}

	for (size_t i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].checkLogData(name, pass))
		{
			loggedUser = &clients[i];
			std::cout << "Login successful! Welcome, " << clients[i].getName() << std::endl;
			return;
		}
	}
	throw std::invalid_argument("Invalid username or password!");
}

void System::registerUser(const MyString& name, const MyString& password, const MyString& EGN, Role role)
{
	if (admin && name == admin->getName())
	{
		throw std::invalid_argument("Admin with this name already exists");
	}
	
	else if (business && name == business->getName())
	{
		throw std::invalid_argument("Business with this name already exists");
	}

	for (size_t i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].getName() == name)
		{
			throw std::invalid_argument("User with this name already exists");
		}
	}
	switch (role)
	{
	case Role::Client:
	{
		clients.push_back(Client(name, password, EGN));
		Client& client = clients[clients.getSize() - 1];
		client.getCart().setClient(&client);
		loggedUser = &client;
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
	std::cout << "You are logged out."<<std::endl;
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

void System::saveSystem()
{
	saveClients();
	saveBusiness();
	saveAdministrator();
}

void System::saveBusiness()
{
	std::ofstream businessFile("business.bin", std::ios::binary);
	if (!businessFile.is_open())
	{
		throw std::runtime_error("Cannot open file for writing");
	}
	business->serialize(businessFile);
	businessFile.close();
}

void System::saveAdministrator()
{
	std::ofstream adminFile("admin.bin", std::ios::binary);
	if (!adminFile.is_open())
	{
		throw std::runtime_error("Cannot open file for writing");
	}
	admin->serialize(adminFile);
	adminFile.close();
}

void System::saveClients()
{
	std::ofstream clientsFile("clients.bin", std::ios::binary);
	if (!clientsFile.is_open())
	{
		throw std::runtime_error("Cannot open file for writing");
	}

	size_t clientsCount = clients.getSize();
	clientsFile.write((const char*)&clientsCount, sizeof(clientsCount));
	for (size_t i = 0; i < clientsCount; i++)
	{
		clients[i].serialize(clientsFile);
	}
	clientsFile.close();
}

void System::loadSystem()
{
	loadClients();
	attachClientsToOrders();
	loadAdministrator();
	loadBusiness();
}

void System::loadBusiness()
{
	std::ifstream file("business.bin", std::ios::binary);
	if (file.is_open())
	{
		business = new Business(file, clients);
	}
	file.close();
}

void System::attachClientsToOrders()
{
	for (size_t i = 0; i < clients.getSize(); ++i)
	{
		Client& client = clients[i];
		OrderManager& orders = client.getOrderManager();

		for (size_t j = 0; j < orders.getSize(); ++j)
		{
			Order& order = orders.getOrder(j);
			order.setClient(&client); 
		}
	}
}

void System::loadAdministrator()
{
	std::ifstream file("admin.bin", std::ios::binary);
	if (file.is_open())
	{
		admin = new Administrator(file);
	}
	file.close();
}

void System::loadClients()
{
	std::ifstream clientsFile("clients.bin", std::ios::binary);
	if (!clientsFile.is_open())
	{
		return;
	}
	
	clients.clear();
	
	size_t clientsCount = 0;
	clientsFile.read((char*)&clientsCount, sizeof(clientsCount));
	for (size_t i = 0; i < clientsCount; i++)
	{
		Client client;
		client.deserialize(clientsFile);
		clients.push_back(client);
	}
	clientsFile.close();
}

Client& System::findClientByEgn(const MyString& EGN)
{
	for (size_t i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].getEGN() == EGN)
		{
			return clients[i];
		}
	}
}

const Client& System::findClientByEgn(const MyString& EGN) const
{
	for (size_t i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].getEGN() == EGN)
		{
			return clients[i];
		}
	}
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

void System::listOrdersClient() const
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
		client->listOrders();
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
		Item item;
		for (size_t i = 0; i < business->getItemsManager().getSize(); i++)
		{
			if (business->getItemsManager().getItem(i).getId() == ID)
			{
				item = business->getItemsManager().getItem(i);
				client->addToCart(item, quantity);
				return;
			}
		}
		throw std::invalid_argument("Item with this ID is not found in the catalog.");
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

void System::orderHistory() const
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
		client->orderHistory();
	}
}

void System::requestRefund(const MyString& reason)
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

void System::addItem(const MyString& name, double price, unsigned quantity, const MyString& description)
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

void System::removeItem(const MyString& name)
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

void System::approveOrder(unsigned ID)
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
		business->approveOrder(ID);
	}
}

void System::rejectOrder(unsigned ID, const MyString& reason)
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
		business->rejectOrder(ID, reason);
	}
}

void System::listRefunds() const
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
		business->listRefunds();
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


