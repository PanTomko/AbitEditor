#pragma once
#include "Command.h"

#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

class Application;

class CommandLine {

	CommandLine();
	DWORD writen;

	std::wstring cleerBuffor;
	std::vector<Command*>comands_vlist;

	wchar_t activeChar;
	wchar_t unActiveChar;

	void get_parm();

public:

	static CommandLine * instance;

	std::wstring comandBuffor;
	Application * app;

	std::vector<std::wstring>parmeters;

	int pos_fix;

	bool active;

	void execute_comand();
	void update(const INPUT_RECORD & record);
	void draw( HANDLE & output );

	CommandLine(CommandLine & Obj) = delete;
	~CommandLine();
};

