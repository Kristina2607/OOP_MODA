#include "InvalidCommand.h"

InvalidCommand::InvalidCommand(System& system):Command(system){}

void InvalidCommand::execute()
{
	std::cout << "Invalid command! " << std::endl;
}
