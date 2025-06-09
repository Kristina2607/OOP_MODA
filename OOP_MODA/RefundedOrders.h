#pragma once 
#include "Command.h"

class RefundedOrders:public Command
{
public:
	RefundedOrders(System& system);
	virtual void execute() override;
};

