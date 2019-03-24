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
	wchar_t wchar;
	unsigned short color;
	auto * app = ToolsManager::toolsManager->app;
	COORD position = record.Event.MouseEvent.dwMousePosition;
	unsigned long writen;
	
	if (app->isMouseOnCanvas(position))
	{
		if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			ReadConsoleOutputCharacterW(
				*app->consoleOutput,
				&wchar,
				1,
				position,
				&writen);

			ToolsManager::toolsManager->setPickedChar(wchar);
		}

		if (record.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
			ReadConsoleOutputAttribute(
				*app->consoleOutput,
				&color,
				1,
				position,
				&writen);

			ToolsManager::toolsManager->setPickedColor(color);
		}
	}
}