#pragma once
#include "Command.h"
class RejectRefund : public Command
{
public:
	RejectRefund(System& system);
	virtual void execute() override;
};

