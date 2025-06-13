#pragma once
#include "Command.h"

class InvalidCommand:public Command
{
public:
	InvalidCommand(System& system);
	virtual void execute() override;
};

