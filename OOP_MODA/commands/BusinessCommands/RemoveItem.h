#pragma once
#include "commands/UserCommands/Command.h"

class RemoveItem :public Command
{
public:
	RemoveItem(System& system);
	virtual void execute() override;
};

