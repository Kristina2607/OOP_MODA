#pragma once
#include "Command.h"

class ConfirmOrder:public Command
{
public:
	ConfirmOrder(System& system);
	virtual void execute() override;
};

