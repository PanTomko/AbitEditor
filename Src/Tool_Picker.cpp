#include "Tool_Picker.h"
#include "ToolsManager.h"
#include "Application.h"
#include "Mouse.h"

Tool_Picker::Tool_Picker() : Tool(L" Picker ")
{
	options.push_back(&color);
}

Tool_Picker::~Tool_Picker()
{
}

void Tool_Picker::input(Event & event)
{

}

void Tool_Picker::update()
{
	wchar_t wchar;
	unsigned short color;
	auto * app = ToolsManager::toolsManager->app;
	COORD position = Mouse::instance->position;
	unsigned long writen;
	
	if (app->isMouseOnCanvas(position))
	{
		if (Mouse::instance->isKeyPressed(MouseKeys::LeftButton)) {
			ReadConsoleOutputCharacterW(
				*app->consoleOutput,
				&wchar,
				1,
				position,
				&writen);

			ToolsManager::toolsManager->setPickedChar(wchar);
		}

		if (Mouse::instance->isKeyPressed(MouseKeys::RightButton)) {
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