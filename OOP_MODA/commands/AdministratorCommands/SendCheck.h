#pragma once
#include "commands/UserCommands/Command.h"

class SendCheck :public Command
{
public:
	SendCheck(System& system);
	virtual void execute() override;
};

