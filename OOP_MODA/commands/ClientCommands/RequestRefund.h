#pragma once
#include "Command.h"

class RequestRefund :public Command
{
public:
	RequestRefund(System& system);
	virtual void execute() override;
};

