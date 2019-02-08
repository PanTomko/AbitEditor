#pragma once
#include "Command.h"
class Command_SaveAs :
	public Command
{
public:

	void execute_command();

	Command_SaveAs();
	~Command_SaveAs();
};

