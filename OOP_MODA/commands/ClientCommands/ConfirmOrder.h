#pragma once
#include "commands/UserCommands/Command.h"

class ConfirmOrder:public Command
{
public:
	ConfirmOrder(System& system);
	virtual void execute() override;
};

