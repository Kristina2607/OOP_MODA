#pragma once
#include "Command.h"

class CustomerInsignts :public Command
{
public:
	CustomerInsignts(System& system);
	virtual void execute() override;
};

