#pragma once
#include "commands/UserCommands/Command.h"

class ViewCart :public Command
{
public:
	ViewCart(System& system);
	virtual void execute() override;
};

