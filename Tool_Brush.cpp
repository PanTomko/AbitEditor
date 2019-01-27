#include "Tool_Brush.h"
#include "Vector2D.h"

#include "ToolsManager.h"
#include "Application.h"
#include "CommandLine.h"

Tool_Brush::Tool_Brush(ToolsManager * toolManger) : Tool(L" Brush ", toolManger)
{
	tmp.znak = L'░';
	tmp.color = 2;
	
	cleer_mark.znak = L' ';
	cleer_mark.color = 7;
	
	options.push_back(&color);
	color.toolManager = toolManger;

	options.push_back(&color2);
	color2.name = L" xdeee ";
	color2.toolManager = toolManger;
}

Tool_Brush::~Tool_Brush()
{
}

void Tool_Brush::update(INPUT_RECORD & record)
{
	if (record.EventType == MOUSE_EVENT)
	{
		auto * app = toolManager->app;
		if (app->activeFile == nullptr) return;
		COORD position = record.Event.MouseEvent.dwMousePosition;

		tmp.color = color.picked_color;

		if (app->isMouseOnCanvas(position))
		{
			if (record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
				app->activeFile->marks[position.Y - app->drawingPos.y][position.X - app->drawingPos.x] = tmp; // y / x
			}

			if (record.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED){
				app->activeFile->marks[position.Y - app->drawingPos.y][position.X - app->drawingPos.x] = cleer_mark; // y / x
			}
		}
		else
		{
			return;
		}

	}
}