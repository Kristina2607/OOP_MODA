#pragma once
#include "commands/UserCommands/Command.h"

class ApplyDiscount :public Command
{
public:
	ApplyDiscount(System& system);
	virtual void execute() override;
};

