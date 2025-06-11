#pragma once
#include "Command.h"
class ListBestSellingProducts :public Command
{
	ListBestSellingProducts(System& system);
	void virtual execute() override;
};

