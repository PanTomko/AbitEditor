#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

#include "Command.h"

class Application;

class CommandLine {

	CommandLine();

public:

	static CommandLine * instance;

	std::wstring comandBuffor;
	std::wstring cleerBuffor;

	std::vector<Command*>comands_vlist;
	std::vector<std::wstring>parmeters;

	Application * app;

	int pos_fix;

	DWORD writen;

	bool active;
	wchar_t activeChar;
	wchar_t unActiveChar;

	void get_parm();
	void execute_comand();

	void update(const INPUT_RECORD & record);
	void draw( HANDLE & output );

	CommandLine(CommandLine & Obj) = delete;
	~CommandLine();
};

