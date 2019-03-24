#include "ToolsManager.h"
#include "Application.h"
#include "CommandLine.h"
#include "HistoryManager.h"

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

void ToolsManager::update(INPUT_RECORD & record)
{
	if (record.EventType == MOUSE_EVENT)
	{

		// update x/y on end of tool menu
		if (app->isMouseOnCanvas(record.Event.MouseEvent.dwMousePosition)) {
			show_xy = true;

			mouse_position_RTC.x = record.Event.MouseEvent.dwMousePosition.X - app->drawingPos.x + app->filePos.x;
			mouse_position_RTC.y = record.Event.MouseEvent.dwMousePosition.Y - app->drawingPos.y + app->filePos.y;

		}
		else {
			show_xy = false;
		}

		if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			if (record.Event.MouseEvent.dwMousePosition.Y == 1 && 
				record.Event.MouseEvent.dwMousePosition.X > 1 &&
				record.Event.MouseEvent.dwMousePosition.X < 3 + menuBuffor.length())
			{
				
				int start_position;
				int end_position;

				for (auto & i : tools)
				{
					start_position = menuBuffor.find(i->name) + 2;
					end_position = start_position + i->name.length();

					if (record.Event.MouseEvent.dwMousePosition.X > start_position &&
						record.Event.MouseEvent.dwMousePosition.X <= end_position)
					{
						if (activeTool != i)
						{
							activeTool = i;
							activeOption = i->options.size() > 0 ? i->options[0] : nullptr;
						}
					}
				}
			}

			if (record.Event.MouseEvent.dwMousePosition.Y == 3 &&
				record.Event.MouseEvent.dwMousePosition.X > 82 &&
				record.Event.MouseEvent.dwMousePosition.X < 82 + optionsBuffer.length() &&
				activeTool != nullptr)
			{
				int start_position;
				int end_position;

				for (auto & i : activeTool->options)
				{
					start_position = optionsBuffer.find(i->name) + 82;
					end_position = start_position + i->name.length();

					if (record.Event.MouseEvent.dwMousePosition.X > start_position &&
						record.Event.MouseEvent.dwMousePosition.X <= end_position)
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
	if (record.EventType == KEY_EVENT && !CommandLine::instance->active)
	{
		Tool * new_tool = nullptr;

		switch (record.Event.KeyEvent.wVirtualKeyCode) 
		{
			// Brush
			case L'B': 
			case L'1': 
				new_tool = tools[0];
					break;
			
			// Picker
			case L'P': 
			case L'2':
				new_tool = tools[1];
				break;

			// Saving
			case L'S':
				if (record.Event.KeyEvent.dwControlKeyState & RIGHT_CTRL_PRESSED ||
					record.Event.KeyEvent.dwControlKeyState & LEFT_CTRL_PRESSED)
				{
					//std::wstring tmp_command_buffer = CommandLine::instance->comandBuffor;
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
		activeTool->update(record);
		
		if( activeOption != nullptr )
			activeOption->update(record);
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
