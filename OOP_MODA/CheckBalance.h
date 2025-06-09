#pragma once
#include "Command.h"

class CheckBalance :public Command
{
public:
	CheckBalance(System& system);
	virtual void execute() override;
};

