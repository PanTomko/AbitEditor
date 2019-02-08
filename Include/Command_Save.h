#pragma once
#include "Command.h"
class Command_Save : public Command
{
public:

	void execute_command();

	Command_Save();
	~Command_Save();
};

