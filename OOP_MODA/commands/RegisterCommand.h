#pragma once
#include "Command.h"

class RegisterCommand : public Command
{
public:
	RegisterCommand(System& system);
	virtual void execute() override;
};

