#pragma once
#include "commands/UserCommands/Command.h"

class ViewProduct :public Command
{
   public:
	ViewProduct(System& system);
	virtual void execute() override;
};

