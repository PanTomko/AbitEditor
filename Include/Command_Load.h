#pragma once
#include "Command.h"
class Command_Load : public Command {
public:

	void execute_command();

	Command_Load();
	~Command_Load();
};

