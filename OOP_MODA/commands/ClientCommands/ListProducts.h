#pragma once
#include "commands/UserCommands/Command.h"

class ListProducts :public Command
{
public:
	ListProducts(System& system);
	virtual void execute() override;
};

