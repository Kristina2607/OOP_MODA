#pragma once
#include "Command.h"

class SendCheck :public Command
{
public:
	SendCheck(System& system);
	virtual void execute() override;
};

