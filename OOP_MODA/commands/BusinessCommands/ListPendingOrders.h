#pragma once
#include "commands/UserCommands/Command.h"

class ListPendingOrders:public Command
{
public:
	ListPendingOrders(System& system);
	virtual void execute() override;
};

