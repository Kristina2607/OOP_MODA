#include "LoadCommand.h"

LoadCommand::LoadCommand(System& system) :Command(system){}

void LoadCommand::execute()
{
	system.loadSystem();
}
