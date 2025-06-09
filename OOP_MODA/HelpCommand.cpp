#include "HelpCommand.h"

HelpCommand::HelpCommand(System& system) :Command(system) {}

void HelpCommand::execute()
{
	system.help();
}
