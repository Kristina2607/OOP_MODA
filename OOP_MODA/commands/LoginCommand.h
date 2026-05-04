#pragma once
#include "Command.h"

class LoginCommand:public Command
{
	public:
		LoginCommand(System& system);
		virtual void execute() override;
};

