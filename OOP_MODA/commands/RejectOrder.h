#pragma once
#include "Command.h"

class RejectOrder:public Command
{
public:
	RejectOrder(System& system);
	void virtual execute() override;
};

