#pragma once
#include "commands/UserCommands/Command.h"

class ApproveOrder:public Command
{
public:
	ApproveOrder(System& system);
	void virtual execute() override;
};

