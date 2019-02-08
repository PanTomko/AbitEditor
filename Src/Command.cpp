#include "Command.h"
#include <iostream>

Command::Command(std::wstring parm_name, int parm_size)
{
	this->parm_name = parm_name;
	this->parm_size = parm_size;
}

Command::~Command()
{
}
