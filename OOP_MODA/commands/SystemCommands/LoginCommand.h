#pragma once
#include "commands/UserCommands/Command.h"

class LoginCommand:public Command
{
	public:
		LoginCommand(System& system);
		virtual void execute() override;
};

