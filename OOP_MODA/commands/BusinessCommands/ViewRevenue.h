#pragma once
#include "commands/UserCommands/Command.h"

class ViewRevenue :public Command
{
public:
	ViewRevenue(System& system);
	virtual void execute() override;
};

