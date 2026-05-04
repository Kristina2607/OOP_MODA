#pragma once
#include "commands/UserCommands/Command.h"

class ApproveRefund:public Command
{
public:
	ApproveRefund(System& system);
	virtual void execute() override;
};

