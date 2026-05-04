#pragma once
#include "Command.h"

class ApplyDiscount :public Command
{
public:
	ApplyDiscount(System& system);
	virtual void execute() override;
};

