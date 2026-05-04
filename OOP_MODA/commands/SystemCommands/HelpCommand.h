#pragma once
#include "commands/UserCommands/Command.h"

class HelpCommand :public Command
{
public:
	HelpCommand(System& system);
	virtual void execute() override;
};

