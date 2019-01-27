#pragma once
#include <string>
//#include "CommandLine.h"
class CommandLine;

class Command
{
public:
	std::wstring parm_name;
	int parm_size;

	virtual void execute_command() = 0;

	CommandLine * comandLine;

	Command( std::wstring parm_name, int parm_size = 1);
	virtual ~Command();
};

