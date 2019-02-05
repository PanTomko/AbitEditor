#include "Tool_Picker.h"
#include "ToolsManager.h"
#include "Application.h"

Tool_Picker::Tool_Picker(ToolsManager * toolManger) : Tool(L" Picker ", toolManger)
{
}

Tool_Picker::~Tool_Picker()
{
}

void Tool_Picker::update(INPUT_RECORD & record)
{
	auto * app = toolManager->app;
	COORD position = record.Event.MouseEvent.dwMousePosition;
	DWORD writen;
	
	if (app->isMouseOnCanvas(position))
	{
		if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			ReadConsoleOutputCharacterW(
				*app->consoleOutput,
				&toolManager->picked_char,
				1,
				position,
				&writen);
		}

		if (record.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
			ReadConsoleOutputAttribute(
				*app->consoleOutput,
				&toolManager->picked_color,
				1,
				position,
				&writen);
			
		}
	}
}