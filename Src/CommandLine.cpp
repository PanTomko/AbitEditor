#include "CommandLine.h"
#include "Application.h"

#include "Command_Save.h"
#include "Command_Load.h"
#include "Command_NewFile.h"

#include <iostream>
#include <algorithm>

CommandLine * CommandLine::instance = new CommandLine();

CommandLine::CommandLine()
{
	//======================== Adding comands
	comands_vlist.push_back(new Command_Save());	// "save"
	comands_vlist.push_back(new Command_Load());	// "load" [path]
	comands_vlist.push_back(new Command_NewFile());	// "new-file" [path] [size x] [size y]
	//========================

	active = true;
	activeChar = L'√';
	unActiveChar = L'X';

	comandBuffor = L"";
	pos_fix = 0;
}

CommandLine::~CommandLine()
{
	for (auto & i : comands_vlist) {
		delete i;
	}
}

void CommandLine::get_parm()
{
	std::wstringstream wss{ comandBuffor };
	std::wstring item;

	while (wss >> item)
	{
		parmeters.push_back(item);
	}
}

void CommandLine::execute_comand()
{
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

void CommandLine::update(const INPUT_RECORD & record)
{
	// 8     - delate
	// 13    - enter
	// 32    - space
	// 37/40 - arows

	// Mouse
	if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		if (record.Event.MouseEvent.dwMousePosition.X == 117 &&
			record.Event.MouseEvent.dwMousePosition.Y == 28) {

			active = active ? false : true;
		}
	}

	// Keyboard
	if (record.EventType == KEY_EVENT && active)
	{
		KEY_EVENT_RECORD key = record.Event.KeyEvent;
	
		if (key.wVirtualKeyCode == 1718 ||
			key.wVirtualKeyCode == 17 ||
			key.wVirtualKeyCode == 16 || // Shift
			key.wVirtualKeyCode == 18) 
				return;

		if (key.bKeyDown)
		{
			// Deleting
			if (key.wVirtualKeyCode == 8) {
				if (comandBuffor.length() > 0) {
					comandBuffor.erase(comandBuffor.length() + pos_fix - 1,1);
				}
				return;
			}

			if (key.wVirtualKeyCode == 37) {
				if (pos_fix - 1 >= comandBuffor.length() && -pos_fix < comandBuffor.length() ) {
					pos_fix--;
				}
				return;
			}

			// Arrows <- ->
			if (key.wVirtualKeyCode == 39) {
				if (pos_fix < 0) {
					pos_fix++;
				}
				return;
			}

			// Enter
			if (key.wVirtualKeyCode == 13) {
				pos_fix = 0;
				execute_comand();
				comandBuffor.clear();
				return;
			}

			if (pos_fix == 0)
				comandBuffor.push_back(key.uChar.UnicodeChar);
			else if (pos_fix < 0) {
				comandBuffor.insert(comandBuffor.length() + pos_fix, &key.uChar.UnicodeChar,1);
			}
		}
	}
}

void CommandLine::draw( HANDLE & output )
{
	WriteConsoleOutputCharacterW(
		output,
		comandBuffor.c_str(),
		comandBuffor.length(),
		{ 3 , 28 },
		&writen);

	SetConsoleCursorPosition(output, { 3 + static_cast<short>(comandBuffor.length() + pos_fix), 28 });

	WriteConsoleOutputCharacterW(
		output,
		active ? &activeChar : &unActiveChar,
		1,
		{ 117 , 28 },
		&writen);
}
