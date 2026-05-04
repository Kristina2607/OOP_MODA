#pragma once
#include "Command.h"
class ListBestSellingProducts :public Command
{

public:
	ListBestSellingProducts(System& system);
	void virtual execute() override;
};

