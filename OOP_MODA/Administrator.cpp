#include "Administrator.h"

Administrator::Administrator(const MyString& name, const MyString& password, const MyString& EGN, Role role)
	: User (name, password, EGN, role) {}

void Administrator::send_checks(unsigned sum, const MyString& code, const MyString& clientEGN)
{
	Check newCheck = Check(code, sum, clientEGN, false);
	checks.push_back(newCheck);
	std::cout << "Check for " << sum << " BGN sent to client with EGN: " << clientEGN << std::endl;
}

void Administrator::customer_insignts(const Client& client) const
{
	std::cout << "Client EGN: " << client.getEGN() << "\n"
		<< "Total orders: " << client.getOrdersCount() << "\n"
		<< "Total spent: " << client.getTotalSpent() << " BGN\n";
}

void Administrator::view_transactions() const
{
	for (size_t i = 0; i < transactions.getSize(); i++)
	{
		transactions[i].printTransactions();
	}
}
