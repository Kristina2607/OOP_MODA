#include "Administrator.h"

Administrator::Administrator(const MyString& name, const MyString& password, const MyString& EGN, Role role)
	: User (name, password, EGN, role) {}

void Administrator::send_checks(unsigned sum, const MyString& code, const MyString& clientEGN)
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

void Administrator::customer_insignts(const Client& client) const
{
	std::cout << "Customer insights: " << std::endl;
	for (size_t i = 0; i < clients.getSize(); i++)
	{
		std::cout << (i + 1) << ". " << clients[i].getName() << "- " << clients[i].getOrdersCount() << ","
			<< clients[i].getTotalSpent() << "BGN spent";
	}
}

void Administrator::view_transactions() const
{
	for (size_t i = 0; i < transactions.getSize(); i++)
	{
		transactions[i].printTransactions();
	}
}
