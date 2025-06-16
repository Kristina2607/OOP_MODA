#include "RateCommand.h"

RateCommand::RateCommand(System& system):Command(system){}

void RateCommand::execute()
{
	unsigned productID;
	std::cout << "Enter ID of the product you want to rate: ";
	std::cin >> productID;

	unsigned rating;
	std::cout << "Enter rating: ";
	std::cin >> rating;

	system.rateOrder(productID, rating);
}
