#pragma once
#include "commands/UserCommands/Command.h"

class Checkout :public Command
{
public:
	Checkout(System& system);
	virtual void execute() override;
};

