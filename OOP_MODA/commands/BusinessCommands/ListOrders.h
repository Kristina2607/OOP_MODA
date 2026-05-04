#pragma once
#include "commands/UserCommands/Command.h"

class ListOrders :public Command
{
public:
	ListOrders(System& system);
	virtual void execute() override;
};

