#include "Tool_Picker.h"
#include "ToolsManager.h"
#include "Application.h"

Tool_Picker::Tool_Picker() : Tool(L" Picker ")
{
	options.push_back(&color);
}

Tool_Picker::~Tool_Picker()
{
}

void Tool_Picker::update(INPUT_RECORD & record)
{
	auto * app = ToolsManager::toolsManager->app;
	COORD position = record.Event.MouseEvent.dwMousePosition;
	DWORD writen;
	
	if (app->isMouseOnCanvas(position))
	{
		if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			ReadConsoleOutputCharacterW(
				*app->consoleOutput,
				&ToolsManager::toolsManager->picked_char,
				1,
				position,
				&writen);
		}

		if (record.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
			ReadConsoleOutputAttribute(
				*app->consoleOutput,
				&ToolsManager::toolsManager->picked_color,
				1,
				position,
				&writen);
			
		}
	}
}