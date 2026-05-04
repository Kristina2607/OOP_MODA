#pragma once
#include "Command.h"

class AddToCart:public Command
{
public:
	AddToCart(System& system);
	virtual void execute() override;
};

