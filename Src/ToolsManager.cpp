#include "ToolsManager.h"
#include "Application.h"
#include "CommandLine.h"
#include "HistoryManager.h"
#include "Keyboard.h"

#include "Tool_Brush.h"
#include "Tool_Picker.h"

#include <iostream>

ToolsManager * ToolsManager::toolsManager = new ToolsManager();

ToolsManager::ToolsManager()
{
	activeTool = nullptr;
	activeOption = nullptr;

	picked_char = L'█';
	picked_color = 15;

	// Ini tools
	tools.push_back(new Tool_Brush());	// 0 for painting on canvas
	tools.push_back(new Tool_Picker());	// 1 for picking colors/chars form canvas 

	show_xy = false;
}

ToolsManager::~ToolsManager()
{
}

void ToolsManager::draw()
{
	menuBuffor = L":";
	for (auto & i : tools)
	{
		menuBuffor += i->name + L":";
	}

	WriteConsoleOutputCharacterW(
		*app->consoleOutput,
		menuBuffor.c_str(),
		menuBuffor.length(),
		{ 3, 1 },
		&writen);

	WORD normal = 224; // 15
	WORD color = 192; // 12

	if (activeTool != nullptr)
	{
		int pos  = 2 + menuBuffor.find(activeTool->name);
		int leng = activeTool->name.length();
		WORD tmp = 0;

		for (int i = 0; i < 118; i++)
		{
			if( i >= pos && i < pos + leng)
				tmp = color;
			else
				tmp = normal;

			WriteConsoleOutputAttribute(
				*app->consoleOutput,
				&tmp,
				1,
				{ 1 + static_cast<short>(i), 1 },
				&writen
			);
		}
		
		// Drawing tool options
		optionsBuffer = L":";

		for (auto & i : activeTool->options)
		{
			optionsBuffer += i->name + L":";
		}

		WriteConsoleOutputCharacterW(
			*app->consoleOutput,
			optionsBuffer.c_str(),
			optionsBuffer.length(),
			{ 83, 3 },
			&writen);
		
		if (activeOption != nullptr)
		{
			int posOption = optionsBuffer.find(activeOption->name);
			int lengOption = activeOption->name.length();

			for (int i = 0; i < 37 ; i++)
			{
				if (i > posOption && i < posOption + lengOption + 1)
					tmp = color;
				else
					tmp = normal;

				WriteConsoleOutputAttribute(
					*app->consoleOutput,
					&tmp,
					1,
					{ 82 + static_cast<short>(i), 3 },
					&writen
				);
			}

			activeOption->draw(app->consoleOutput);
		}
		else
		{
			for (int i = 0; i <37; i++)
			{
				WriteConsoleOutputAttribute(
					*app->consoleOutput,
					&normal,
					1,
					{ 82 + static_cast<short>(i), 3 },
					&writen
				);
			}
		}
	}
	else
	{
		for (int i = 0; i <118; i++)
		{
			WriteConsoleOutputAttribute(
				*app->consoleOutput,
				&normal,
				1,
				{ 1 + static_cast<short>(i), 1 },
				&writen
			);
		}

		for (int i = 0; i <37; i++)
		{
			WriteConsoleOutputAttribute(
				*app->consoleOutput,
				&normal,
				1,
				{ 82 + static_cast<short>(i), 3 },
				&writen
			);
		}
	}

	// Drawing x/y and the end of tool menu
	if (show_xy) {
		std::wstring xyBuffer;
		xyBuffer += L"x : " + std::to_wstring(mouse_position_RTC.x);
		xyBuffer += L" | y : " + std::to_wstring(mouse_position_RTC.y);

		WriteConsoleOutputCharacterW(
			*app->consoleOutput,
			xyBuffer.c_str(),
			xyBuffer.length(),
			{ 100, 1 },
			&writen);
	}
	
}

void ToolsManager::input(Event & event)
{
	if (event.event_type == Event::Type::Mouse)
	{
		// update x/y on end of tool menu
		if (app->isMouseOnCanvas(event.mouseEvent.position)) {
			show_xy = true;

			mouse_position_RTC.x = event.mouseEvent.position.X - app->drawingPos.x + app->filePos.x;
			mouse_position_RTC.y = event.mouseEvent.position.Y - app->drawingPos.y + app->filePos.y;

		}
		else {
			show_xy = false;
		}

		if (event.mouseEvent.isKeyJustRelased(MouseKeys::LeftButton))
		{
			if (event.mouseEvent.position.Y == 1 &&
				event.mouseEvent.position.X > 1 &&
				event.mouseEvent.position.X < 3 + menuBuffor.length())
			{
				
				int start_position;
				int end_position;

				for (auto & i : tools)
				{
					start_position = menuBuffor.find(i->name) + 2;
					end_position = start_position + i->name.length();

					if (event.mouseEvent.position.X > start_position &&
						event.mouseEvent.position.X <= end_position)
					{
						if (activeTool != i)
						{
							activeTool = i;
							activeOption = i->options.size() > 0 ? i->options[0] : nullptr;
						}
					}
				}
			}

			if (event.mouseEvent.position.Y == 3 &&
				event.mouseEvent.position.X > 82 &&
				event.mouseEvent.position.X < 82 + optionsBuffer.length() &&
				activeTool != nullptr)
			{
				int start_position;
				int end_position;

				for (auto & i : activeTool->options)
				{
					start_position = optionsBuffer.find(i->name) + 82;
					end_position = start_position + i->name.length();

					if (event.mouseEvent.position.X > start_position &&
						event.mouseEvent.position.X <= end_position)
					{
						if (activeOption != i)
						{
							activeOption = i;
						}
					}
				}
			}
		}
	}

	// Shortcuts
	if (event.event_type == Event::Type::Keyboard && !CommandLine::instance->active)
	{
		Tool * new_tool = nullptr;

		switch (event.keyboardEvent.key) 
		{
			// Brush
			case Key::B: 
			case Key::Num1:
				new_tool = tools[0];
					break;
			
			// Picker
			case Key::P:
			case Key::Num2:
				new_tool = tools[1];
				break;

			// Saving
			case Key::S:
				if (Keyboard::instance->keys[Key::Ctrl] & 0b001 )
				{
					CommandLine::instance->comandBuffor = L"save";
					CommandLine::instance->execute_comand();
					CommandLine::instance->comandBuffor = L"log->saved";
				}
				break;

			default:
				break;
		}

		if ( new_tool != nullptr && activeTool != new_tool) {
			activeTool = new_tool;
			activeOption = activeTool->options.size() > 0 ? activeTool->options[0] : nullptr;
		}
	}

	if (activeTool != nullptr) {
		activeTool->input(event);
		
		if( activeOption != nullptr )
			activeOption->input(event);
	}
}

void ToolsManager::update()
{
	if (activeTool != nullptr) {
		activeTool->update();

		if (activeOption != nullptr)
			activeOption->update();
	}
}

unsigned short ToolsManager::getPickedColor()
{
	return picked_color;
}

wchar_t ToolsManager::getPickedChar()
{
	return picked_char;
}

void ToolsManager::setPickedColor(const unsigned short & color)
{
	if (picked_color != color)
	{
		HistoryManager::instance->saveHistory(&picked_color, picked_color);
		picked_color = color;
	}
}

void ToolsManager::setPickedChar(const wchar_t & wchar)
{
	if (picked_char != wchar)
	{
		HistoryManager::instance->saveHistory(&picked_char, picked_char);
		picked_char = wchar;
	}
}
