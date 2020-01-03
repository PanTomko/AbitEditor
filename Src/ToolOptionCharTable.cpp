#include "ToolOptionCharTable.h"
#include "ToolsManager.h"
#include "Application.h"
#include "Mouse.h"

#include <iostream>
#include <windows.h>

ToolOptionCharTable::ToolOptionCharTable() : ToolOption( L" Style " )
{
	// Ini char tables
	commonTable.name = L"common";
	commonTable.chars_ranges.push_back(Range{ 0x0061, 0x007A });	// a --> z
	commonTable.chars_ranges.push_back(Range{ 0x0041, 0x005A });	// A --> Z
	commonTable.chars_ranges.push_back(Range{ 0x0030, 0x0039 });	// 0 --> 9

	specialTable.name = L"special";
	specialTable.chars_ranges.push_back(Range{ 0x0021, 0x002F});	// ! --> /
	specialTable.chars_ranges.push_back(Range{ 0x003A, 0x0040 });	// : --> @
	specialTable.chars_ranges.push_back(Range{ 0x005B, 0x0060 });	// [ --> `
	specialTable.chars_ranges.push_back(Range{ 0x2183, 0x2321 });	// Ↄ --> ⌡
	
	extraTable.name = L"extra";
	extraTable.chars_ranges.push_back(Range{ 0x2580, 0x25E6 });		// ▀ --> ◦
	extraTable.chars_ranges.push_back(Range{ 0x263A, 0x2736 });		// ☺ --> ✶
	extraTable.chars_ranges.push_back(Range{ 0x2500, 0x257F });		// ─ --> ╿

	smallDots.name = L"small";
	smallDots.chars_ranges.push_back(Range{ L'ʹ', L'·' });			// ʹ --> ·

	charTables.push_back(&commonTable);
	charTables.push_back(&specialTable);
	charTables.push_back(&extraTable);
	charTables.push_back(&smallDots);

	for (auto & i : charTables) {
		i->calculateChars();
	}

	menu_position = 0;
	activeCharTable = charTables[menu_position];
}

ToolOptionCharTable::~ToolOptionCharTable()
{
}

void ToolOptionCharTable::draw(HANDLE * consoleOutput)
{
	COORD startPos = { 84, 5 };
	COORD drawPos = { 0, 2 };
	WORD color = 12;

	// drawing active CharTable
	for (wchar_t & i : activeCharTable->chars)
	{
		if (i == L'\0')
		{
			drawPos.Y += 2;
			drawPos.X = 0;
			continue;
		}

		COORD pos = { startPos.X + drawPos.X, startPos.Y + drawPos.Y };
		WriteConsoleOutputCharacterW( *consoleOutput, &i, 1, pos, &writen);

		drawPos.X += 2;
		if (drawPos.X > 32) {
			drawPos.Y += 1;
			drawPos.X = 0;
		}
	}

	// drawing interface
	CharTable * left_table;
	CharTable * right_table;

	if (menu_position == 0) {
		left_table = charTables[charTables.size() - 1];
	}
	else {
		left_table = charTables[menu_position - 1];
	}

	if (menu_position == charTables.size() - 1) {
		right_table = charTables[0];
	}
	else {
		right_table = charTables[menu_position + 1];
	}

	std::wstring menuBuffer = L" << " + activeCharTable->name + L" >> ";
	short space = (37 - static_cast<short>(menuBuffer.length())) / 2 ;
	menuBuffer.insert(0, left_table->name);
	menuBuffer += right_table->name;

	COORD pos = { startPos.X + space - 2 - static_cast<short>(left_table->name.length()), startPos.Y };
	WriteConsoleOutputCharacterW(*consoleOutput, menuBuffer.c_str(), menuBuffer.length(), pos, &writen);
	
	for (short x = 0; x < activeCharTable->name.length(); x++)
	{
		WriteConsoleOutputAttribute(
			*consoleOutput, 
			&color, 
			1, 
			{ pos.X+ static_cast<short>(left_table->name.length()) + 4 + x, pos.Y }, 
			&writen);
	}

	for (short y = 0; y < 4; y++)
	{
		for (short x = 0; x < 9; x++)
		{
			wchar_t wchar{ ToolsManager::toolsManager->getPickedChar() };
			WriteConsoleOutputCharacterW(
				*consoleOutput,
				&wchar,
				1,
				{ startPos.X + x + 12, startPos.Y + y + 17 },
				&writen);

			color += 1;
		}
	}
}

void ToolOptionCharTable::input(Event & event)
{
	if (event.event_type == Event::Type::Mouse)
	{
		if (event.mouseEvent.isKeyJustRelased(MouseKeys::LeftButton))
		{
			auto & app = ToolsManager::toolsManager->app;
			wchar_t tmp;

			if (event.mouseEvent.position.Y == 5 && event.mouseEvent.position.X >= 83 && event.mouseEvent.position.X <= 118)
			{
				ReadConsoleOutputCharacterW(*app->consoleOutput, &tmp, 1, event.mouseEvent.position, &writen);
				if (tmp == L'<') {
					menu_position--;
					if (menu_position < 0)
						menu_position = charTables.size() - 1;
				}
				else if (tmp == L'>') {
					menu_position++;
					if (menu_position > charTables.size() - 1)
						menu_position = 0;
				}

				activeCharTable = charTables[menu_position];
			}
		}
	}
}

void ToolOptionCharTable::update()
{
	if (Mouse::instance->isKeyPressed(MouseKeys::LeftButton))
	{
		COORD mous_position = Mouse::instance->position;
		auto & app = ToolsManager::toolsManager->app;
		wchar_t tmp;

		if (mous_position.X >= 83 && mous_position.X <= 118 && mous_position.Y >= 6 && mous_position.Y <= 26){
			ReadConsoleOutputCharacterW(*app->consoleOutput, &tmp, 1, mous_position, &writen);
			if (tmp != L' ') {
				ToolsManager::toolsManager->setPickedChar(tmp);
			}	
		}
	}
}