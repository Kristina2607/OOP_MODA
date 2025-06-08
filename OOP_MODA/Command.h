#pragma once
#include "MyString.h"
#include "UserManager.h"

class Command
{
protected:
	UserManager& userManager;

public:
	Command(UserManager& userManager);
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class LogoutCommand : public Command
{
	virtual void execute() override;
};

class LoginCommand : public Command
{
	virtual void execute() override;
};

class HelpMenu :public Command
{
	virtual void execute() override;
};

class ViewProfile : public Command
{
	virtual void execute() override;
};



