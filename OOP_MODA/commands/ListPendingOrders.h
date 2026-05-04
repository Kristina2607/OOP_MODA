#pragma once
#include "Command.h"

class ListPendingOrders:public Command
{
public:
	ListPendingOrders(System& system);
	virtual void execute() override;
};

