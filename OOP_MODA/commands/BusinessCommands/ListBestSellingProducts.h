#pragma once
#include "commands/UserCommands/Command.h"
class ListBestSellingProducts :public Command
{

public:
	ListBestSellingProducts(System& system);
	void virtual execute() override;
};

