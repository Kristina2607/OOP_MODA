#pragma once
#include "commands/UserCommands/Command.h"

class LoadCommand: public Command
{
public:
	LoadCommand(System& system);
	virtual void execute() override;
};

