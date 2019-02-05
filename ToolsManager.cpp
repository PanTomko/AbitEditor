#include "ToolsManager.h"
#include "Application.h"
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
	tools.push_back(new Tool_Brush());	// for painting on canvas
	tools.push_back(new Tool_Picker());	// for picking colors/chars form canvas 
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
}

void ToolsManager::update(INPUT_RECORD & record)
{
	if (record.EventType == MOUSE_EVENT)
	{
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

	if (activeTool != nullptr) {
		activeTool->update(record);
		
		if( activeOption != nullptr )
			activeOption->update(record);
	}
}
