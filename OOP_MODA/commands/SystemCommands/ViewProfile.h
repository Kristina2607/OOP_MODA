#pragma once
#include "commands/UserCommands/Command.h"

class ViewProfile :public Command
{
public:
	ViewProfile(System& system);
	virtual void execute() override;
};

