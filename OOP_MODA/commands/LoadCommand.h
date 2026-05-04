#pragma once
#include "Command.h"

class LoadCommand: public Command
{
public:
	LoadCommand(System& system);
	virtual void execute() override;
};

