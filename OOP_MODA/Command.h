#pragma once
#include "MyString.h"
#include "System.h"

class Command
{
protected:
	System& system;

public:
	Command(System& system);
	virtual ~Command() = default;
	virtual void execute() = 0;
};






