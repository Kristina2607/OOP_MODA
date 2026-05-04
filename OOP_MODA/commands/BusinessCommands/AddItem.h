#pragma once
#include "commands/UserCommands/Command.h"

class AddItem :public Command
{
   public:
	AddItem(System& system);
	virtual void execute() override;
};

