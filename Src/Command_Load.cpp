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
	//if (CommandLine::instance->parmeters.size() == parm_size)
	//	CommandLine::instance->app->loadBitA(CommandLine::instance->parmeters[1]);
}
