#include "Command_Save.h"
#include "CommandLine.h"
#include "Application.h"

#include <iostream>


void Command_Save::execute_command()
{
	if( comandLine->app->activeFile != nullptr)
		comandLine->app->activeFile->save();
}

Command_Save::Command_Save() : Command( L"save", 1 )
{
}

Command_Save::~Command_Save()
{
	//std::wcout << L" Delete Comand" << std::endl;
}
