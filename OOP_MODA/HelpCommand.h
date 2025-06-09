#pragma once
#include "Command.h"

class HelpCommand :public Command
{
public:
	HelpCommand(System& system);
	virtual void execute() override;
};

