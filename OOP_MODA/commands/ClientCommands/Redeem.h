#pragma once
#include "commands/UserCommands/Command.h"

class Redeem:public Command
{
public:
	Redeem(System& system);
	virtual void execute() override;
};

