#pragma once
#include "Command.h"

class ViewProfile :public Command
{
public:
	ViewProfile(System& system);
	virtual void execute() override;
};

