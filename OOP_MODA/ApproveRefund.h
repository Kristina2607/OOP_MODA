#pragma once
#include "Command.h"

class ApproveRefund:public Command
{
	ApproveRefund(System& system);
	virtual void execute() override;
};

