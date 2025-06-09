#pragma once
#include "Command.h"

class RemoveFromCart:public Command
{
public:
	RemoveFromCart(System& system);
	virtual void execute() override;
};

