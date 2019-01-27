#include "Command_Load.h"
#include "CommandLine.h"
#include "Application.h"

Command_Load::Command_Load() : Command( L"load", 2)
{
}

Command_Load::~Command_Load()
{
}

void Command_Load::execute_command()
{
	if (comandLine->parmeters.size() == parm_size)
	{
		comandLine->app->loadBitA(comandLine->parmeters[1]);
	}
}
