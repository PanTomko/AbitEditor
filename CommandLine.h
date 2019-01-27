#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

#include "Command.h"

class Application;

class CommandLine
{
public:
	CommandLine();
	~CommandLine();

	std::wstring comandBuffor;
	std::wstring cleerBuffor;

	std::vector<Command*>comands_vlist;

	std::vector<std::wstring>parmeters;

	void get_parm();
	void execute_comand();

	Application * app;

	int pos_fix;

	DWORD writen;

	void update( const KEY_EVENT_RECORD & key);
	void draw( HANDLE & output );
};

