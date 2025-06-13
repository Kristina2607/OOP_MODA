#include "LogoutCommand.h"

LogoutCommand::LogoutCommand(System& system):Command(system) {}

void LogoutCommand::execute()
{
	system.logout();
}
