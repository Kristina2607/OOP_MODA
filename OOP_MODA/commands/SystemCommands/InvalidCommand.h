#pragma once
#include "commands/UserCommands/Command.h"

class InvalidCommand:public Command
{
public:
	InvalidCommand(System& system);
	virtual void execute() override;
};

