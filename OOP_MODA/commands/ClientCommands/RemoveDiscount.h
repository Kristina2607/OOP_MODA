#pragma once 
#include "Command.h"

class RemoveDiscount:public Command
{
public:
	RemoveDiscount(System& system);
	virtual void execute() override;
};

