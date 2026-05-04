#pragma once
#include "commands/UserCommands/Command.h"

class CheckBalance :public Command
{
public:
	CheckBalance(System& system);
	virtual void execute() override;
};

