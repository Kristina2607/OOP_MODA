#pragma once
#include "Command.h"

class RemoveItem :public Command
{
public:
	RemoveItem(System& system);
	virtual void execute() override;
};

