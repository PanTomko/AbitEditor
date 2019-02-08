#pragma once
#include "Command.h"
class Command_NewFile : public Command
{
public:

	void execute_command();

	Command_NewFile();
	~Command_NewFile();
};

