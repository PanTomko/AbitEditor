#pragma once
#include <string>

class CommandLine;

class Command {
public:
	CommandLine * comandLine;
	std::wstring parm_name;
	int parm_size;

	virtual void execute_command() = 0;

	Command( std::wstring parm_name, int parm_size = 1);
	virtual ~Command();
};

