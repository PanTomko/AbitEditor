#include <iostream>

#include "ToolOptionColor.h"
#include "ToolsManager.h"
#include "Application.h"

ToolOptionColor::ToolOptionColor() : ToolOption( L" Color " )
{
	picked_color = 7;
	default_znak = L'x';
	znak = nullptr;
}

ToolOptionColor::~ToolOptionColor()
{
}

void ToolOptionColor::update(INPUT_RECORD & record)
{
	if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		// X - 84/116   Y - 5/19
		COORD mouse = record.Event.MouseEvent.dwMousePosition;
		wchar_t tmp;
		
		if (mouse.X >= 84 && mouse.X <= 116 && mouse.Y >= 5 && mouse.Y <= 19)
		{
			WORD tmp_color;
			HANDLE active_buffor;
			if (ToolsManager::toolsManager->app->consoleOutput == &ToolsManager::toolsManager->app->consoleOutputBufforOne) {
				active_buffor = ToolsManager::toolsManager->app->consoleOutputBufforTwo;
			}
			else {
				active_buffor = ToolsManager::toolsManager->app->consoleOutputBufforOne;
			}

			ReadConsoleOutputAttribute(
				active_buffor,
				&tmp_color,
				1,
				mouse,
				&writen);
			
			ReadConsoleOutputCharacterW(active_buffor, &tmp, 1, mouse, &writen);

			if (tmp != L' ') {
				picked_color = tmp_color;
				ToolsManager::toolsManager->picked_color = tmp_color;
			}
		}
	}
}

void ToolOptionColor::draw(HANDLE * consoleOutput)
{
	// add 83 to get start pos
	COORD startPos = { 84, 5 };
	COORD drawPows;
	WORD color = 0;

	short space;

	const wchar_t * show_znak = L"●";
	
	for (short y = 0; y < 16; y += 2)
	{
		for (short x = 0; x < 32; x += 1)
		{
			if (x >= 16)
				space = 1;
			else
				space = 0;

			WriteConsoleOutputCharacterW(
				*consoleOutput,
				show_znak,
				1,
				{ startPos.X + x + space, startPos.Y + y },
				&writen);

			WriteConsoleOutputAttribute(
				*consoleOutput,
				&color,
				1,
				{ startPos.X + x + space, startPos.Y + y },
				&writen
			);
			color += 1;
		}
	}

	for (short y = 0; y < 4; y++)
	{
		for (short x = 0; x < 9; x++)
		{

			WriteConsoleOutputCharacterW(
				*consoleOutput,
				&ToolsManager::toolsManager->picked_char,
				1,
				{ startPos.X + x + 12, startPos.Y + y + 17 },
				&writen);

			WriteConsoleOutputAttribute(
				*consoleOutput,
				&picked_color,
				1,
				{ startPos.X + x + 12, startPos.Y + y + 17 },
				&writen
			);
			color += 1;
		}
	}
}
