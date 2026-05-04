#pragma once
#include "commands/UserCommands/Command.h"

class ListRefunds:public Command
{
public:
	ListRefunds(System& system);
	virtual void execute() override;
};

