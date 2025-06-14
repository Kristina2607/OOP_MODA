#pragma once
#include "Command.h"

class ApproveOrder:public Command
{
public:
	ApproveOrder(System& system);
	void virtual execute() override;
};

