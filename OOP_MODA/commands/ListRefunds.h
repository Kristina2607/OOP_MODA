#pragma once
#include "Command.h"

class ListRefunds:public Command
{
public:
	ListRefunds(System& system);
	virtual void execute() override;
};

