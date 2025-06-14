#include "Administrator.h"

Administrator::Administrator(MyString name, MyString password, MyString EGN)
	: User(name, password, EGN, Role::Admin)
{}

void Administrator::viewProfile() const
{
	std::cout << "Admin profile" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "EGN: " << this->EGN << std::endl;
}

void Administrator::help() const
{
	std::cout << "You are allowed to:" << std::endl;
	std::cout << "> send_checks" << std::endl;
	std::cout << "> customer_insights" << std::endl;
	std::cout << "> view_transactions" << std::endl;
}

User* Administrator::clone() const
{
	throw std::logic_error("Cannot clone business");
}

void Administrator::sendChecks(unsigned sum, const MyString& code, const MyString& clientEGN)
{
	if (sum <= 0)
	{
		throw std::invalid_argument("Amount must be positive!");
	}
	if (code.getSize() != 4)
	{
		throw std::invalid_argument("Code must be 4 characters!");
	}
	for (size_t i = 0;i<checks.getSize();i++) 
	{
		if (checks[i].isValidCode(code) && !checks[i].getIsRedeemed())
		{
			throw std::logic_error("Check code must be unique!");
		}
	}
	Check newCheck = Check(code, sum, clientEGN, false);
	checks.push_back(newCheck);
	std::cout << "Check for " << sum << " BGN sent to client with EGN: " << clientEGN << std::endl;
}

void Administrator::customerInsights() const
{
	std::cout << "Customer insights: " << std::endl;
	for (size_t i = 0; i < clients.getSize(); i++)
	{
		std::cout << (i + 1) << ". " << clients[i].getName() << "- " << clients[i].getOrdersCount() << ","
			<< clients[i].getTotalSpent() << "BGN spent";
	}
}

void Administrator::viewTransactions() const
{
	for (size_t i = 0; i < transactions.getSize(); i++)
	{
		transactions[i].printTransactions();
	}
}

