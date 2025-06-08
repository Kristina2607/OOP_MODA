#pragma once
#include "Command.h"
#include "UserManager.h"

class RegisterCommand : public Command
{
public:
	virtual void execute() override;
};

