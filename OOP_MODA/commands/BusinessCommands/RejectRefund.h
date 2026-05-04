#pragma once
#include "commands/UserCommands/Command.h"
class RejectRefund : public Command
{
public:
	RejectRefund(System& system);
	virtual void execute() override;
};

