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
	if (comandLine->parmeters.size() == 4)
	{
		delete comandLine->app->activeFile;

		comandLine->app->drawLaout();

		comandLine->app->activeFile = new BitA{
			comandLine->parmeters[1],
			static_cast<unsigned int>(std::stoi(comandLine->parmeters[2])),
			static_cast<unsigned int>(std::stoi(comandLine->parmeters[3])),
		};

		comandLine->app->activeFile->populate(L' ', 7);
	}
}
