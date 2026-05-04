#pragma once
#include "Command.h"
class LogoutCommand :public Command
{
public:
	LogoutCommand(System& system);
	virtual void execute() override;
};

