#include "CommandLine.h"
#include "Application.h"
#include <iostream>
#include <algorithm>

// Comands
#include "Command_Save.h"
#include "Command_Load.h"
#include "Command_NewFile.h"

CommandLine::CommandLine()
{
	//======================== Adding comands
	
	comands_vlist.push_back(new Command_Save());	// "save"
	comands_vlist.push_back(new Command_Load());	// "load" [path]
	comands_vlist.push_back(new Command_NewFile());	// "new-file" [path] [size x] [size y]

	for (auto & i : comands_vlist)
	{
		i->comandLine = this;
	}

	//= end =

	comandBuffor = L"";
	pos_fix = 0;
}

CommandLine::~CommandLine()
{
	for (auto & i : comands_vlist)
	{
		delete i;
	}
}

void CommandLine::get_parm()
{
	std::wstringstream wss{comandBuffor};
	std::wstring item;

	while (wss >> item)
	{
		parmeters.push_back(item);
	}
}

void CommandLine::execute_comand()
{
	// is there sutch comand
	// is there enought params
	// are params of good type/format

	get_parm();
	
	for (auto & i : comands_vlist)
	{
		if (i->parm_name == parmeters[0])
		{
			i->execute_command();
			break;
		}
	}

	parmeters.clear();
}

void CommandLine::update( const KEY_EVENT_RECORD & key )
{
	// 8     - delate
	// 13    - enter
	// 32    - space
	// 37/40 - arows

	// ignore shift
	if (key.wVirtualKeyCode == 1718 ||
		key.wVirtualKeyCode == 17 ||
		key.wVirtualKeyCode == 16 || // Shift
		key.wVirtualKeyCode == 18) 
			return;

	if (key.bKeyDown)
	{
		// Deleting
		if (key.wVirtualKeyCode == 8)
		{
			if (comandBuffor.length() > 0)
			{
				comandBuffor.erase(comandBuffor.length() + pos_fix - 1,1);
			}
			return;
		}

		if (key.wVirtualKeyCode == 37)
		{
			if (pos_fix - 1 >= comandBuffor.length() && -pos_fix < comandBuffor.length() )
			{
				pos_fix--;
			}
			return;
		}

		// Arrows <- ->
		if (key.wVirtualKeyCode == 39)
		{
			if (pos_fix < 0)
			{
				pos_fix++;
			}
			return;
		}

		// Enter
		if (key.wVirtualKeyCode == 13)
		{
			pos_fix = 0;
			execute_comand();
			comandBuffor.clear();
			return;
		}

		//comandBuffor += key.uChar.UnicodeChar;
		if (pos_fix == 0)
			comandBuffor.push_back(key.uChar.UnicodeChar);
		else if (pos_fix < 0)
		{
			comandBuffor.insert(comandBuffor.length() + pos_fix, &key.uChar.UnicodeChar,1);
		}
		//comandBuffor += std::to_string((int)key.uChar.UnicodeChar);
	}
}

void CommandLine::draw( HANDLE & output )
{
	//
	//SetConsoleCursorPosition(output, { 3 , 28 });
	cleerBuffor = L"                                                                                                                    ";
	for (int i = 0; i < comandBuffor.length(); i++)
	{
		cleerBuffor[i] = comandBuffor[i];
	}

	WriteConsoleOutputCharacterW(
		output,
		cleerBuffor.c_str(),
		cleerBuffor.length(),
		{ 3 , 28 },
		&writen);

	SetConsoleCursorPosition(output, { 3 + static_cast<short>(comandBuffor.length() + pos_fix), 28 });
}
