#pragma once
#include "Command.h"

class OrderHistory: public Command
{
public:
	OrderHistory(System& system);
	virtual void execute() override;
};

