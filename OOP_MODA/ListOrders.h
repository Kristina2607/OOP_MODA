#pragma once
#include "Command.h"

class ListOrders :public Command
{
public:
	ListOrders(System& system);
	virtual void execute() override;
};

