#pragma once
#include "commands/UserCommands/Command.h"

class CustomerInsignts :public Command
{
public:
	CustomerInsignts(System& system);
	virtual void execute() override;
};

