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

	lastKey = Key::Null;
	keyRepeatCount = 0;
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
	pos_fix = 0;
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
	comandBuffor.clear();
}

void CommandLine::input(Event & event)
{
	// Mouse
	// TODO : Add mouse functionality

	if (event.event_type == Event::Type::Mouse)
	{
		if (event.mouseEvent.isKeyJustRelased(MouseKeys::LeftButton))
		{
			if (event.mouseEvent.position.X == 117 &&
				event.mouseEvent.position.Y == 28) {

				active = active ? false : true;
			}
		}
	}
	
	// Keyboard
	if (event.event_type == Event::Type::Keyboard && active)
	{
		if (event.keyboardEvent.key == lastKey) ++keyRepeatCount;
		else {
			keyRepeatCount = 0;
			lastKey = event.keyboardEvent.key;
		}

		if (!event.keyboardEvent.isKeyPressed(lastKey)) lastKey = Key::Null;

		// Deleting
		if (event.keyboardEvent.isKeyJustPressed(Key::Backspace) || (keyRepeatCount > 10 && event.keyboardEvent.isKeyPressed(Key::Backspace))) {
			if (comandBuffor.length() > 0) {
				comandBuffor.erase(comandBuffor.length() + pos_fix - 1,1);
			}
			return;
		}
		
		// Arrows <- ->
		if (event.keyboardEvent.isKeyJustPressed(Key::LeftArrow) || (keyRepeatCount > 10 && event.keyboardEvent.isKeyPressed(Key::LeftArrow))) {
			if (pos_fix - 1 >= comandBuffor.length() && -pos_fix < comandBuffor.length() ) {
				pos_fix--;
			}
			return;
		}

		if (event.keyboardEvent.isKeyJustPressed(Key::RightArrow) || (keyRepeatCount > 10 && event.keyboardEvent.isKeyPressed(Key::RightArrow))) {
			if (pos_fix < 0) {
				pos_fix++;
			}
			return;
		}

		// Enter
		if (event.keyboardEvent.isKeyJustPressed(Key::Enter)) {
			execute_comand();
			return;
		}
		
		// Unicode typing

		if (event.keyboardEvent.unicode != L'\0' && (event.keyboardEvent.isKeyJustPressed(lastKey) || keyRepeatCount > 10) )
		{
			if (pos_fix == 0)
				comandBuffor.push_back(event.keyboardEvent.unicode);
			else if (pos_fix < 0) {
				comandBuffor.insert(comandBuffor.length() + pos_fix, &event.keyboardEvent.unicode, 1);
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

	WORD color = 63;
	DWORD writen;

	WriteConsoleOutputAttribute(output, &color, 1, { 3 + static_cast<short>(comandBuffor.length() + pos_fix), 28 }, &writen);
}
