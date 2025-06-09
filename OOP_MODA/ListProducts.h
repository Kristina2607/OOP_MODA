#pragma once
#include "Command.h"

class ListProducts :public Command
{
public:
	ListProducts(System& system);
	virtual void execute() override;
};

