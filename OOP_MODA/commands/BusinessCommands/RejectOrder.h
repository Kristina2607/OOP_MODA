#pragma once
#include "commands/UserCommands/Command.h"

class RejectOrder:public Command
{
public:
	RejectOrder(System& system);
	void virtual execute() override;
};

