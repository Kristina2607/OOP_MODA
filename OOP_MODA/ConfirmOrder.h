#pragma once
#include "Command.h"

class ConfirmOrder:public Command
{
	ConfirmOrder(System& system);
	virtual void execute() override;
};

