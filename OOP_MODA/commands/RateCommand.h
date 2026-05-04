#pragma once
#include "Command.h"
class RateCommand :public Command
{
public:
	RateCommand(System& system);
	virtual void execute() override;
};

