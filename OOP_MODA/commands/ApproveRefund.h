#pragma once
#include "Command.h"

class ApproveRefund:public Command
{
public:
	ApproveRefund(System& system);
	virtual void execute() override;
};

