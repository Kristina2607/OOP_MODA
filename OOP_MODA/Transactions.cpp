#include "Transactions.h"

Transactions::Transactions(const MyString& reciever, const MyString& sender, unsigned sum)
    :from(sender), to(reciever), sum(sum) {}

void Transactions::printTransactions() const
{
    std::cout<< "Transaction: " << sum <<" from " << from << " to " << to;
}
