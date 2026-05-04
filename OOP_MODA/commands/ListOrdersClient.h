#pragma once
#include "Command.h"

class ListOrdersClient:public Command
{
public:
	ListOrdersClient(System& system);
	virtual void execute() override;
};

