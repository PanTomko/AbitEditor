#include "Command_NewFile.h"
#include "CommandLine.h"
#include "Application.h"

#include "BitA.h"

Command_NewFile::Command_NewFile() : Command( L"new-file", 4)
{
}

Command_NewFile::~Command_NewFile()
{
}

void Command_NewFile::execute_command()
{
	/*if (CommandLine::instance->parmeters.size() == 4)
	{
		delete CommandLine::instance->app->activeFile;

		CommandLine::instance->app->drawLaout();

		CommandLine::instance->app->activeFile = new BitA{
			CommandLine::instance->parmeters[1],
			static_cast<unsigned int>(std::stoi(CommandLine::instance->parmeters[2])),
			static_cast<unsigned int>(std::stoi(CommandLine::instance->parmeters[3])),
		};

		CommandLine::instance->app->activeFile->populate(L' ', 7);
	}*/
}
