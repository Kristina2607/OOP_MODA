#pragma once
#include "commands/UserCommands/Command.h"

class RegisterCommand : public Command
{
public:
	RegisterCommand(System& system);
	virtual void execute() override;
};

