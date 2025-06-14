#pragma once
#include "Command.h"

class SaveCommand:public Command
{
public:
	SaveCommand(System& system);
	virtual void execute() override;
};

