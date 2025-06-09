#pragma once
#include "Command.h"

class ViewCart :public Command
{
public:
	ViewCart(System& system);
	virtual void execute() override;
};

