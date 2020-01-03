#include "Tool_Brush.h"
#include "Vector2D.h"
#include "ToolsManager.h"
#include "Application.h"
#include "CommandLine.h"
#include "Mouse.h"
#include "HistoryManager.h"
#include "VectorMarkHistory.h"

Tool_Brush::Tool_Brush() : Tool(L" Brush ")
{
	tmp.znak = L'░';
	tmp.color = 2;
	
	cleer_mark.znak = L' ';
	cleer_mark.color = 7;
	
	options.push_back(&color);
	color.znak = &wcharTable.char_to_use;

	options.push_back(&wcharTable);
}

Tool_Brush::~Tool_Brush()
{
}

void Tool_Brush::input(Event & event)
{
	if (event.event_type == Event::Type::Mouse)
	{
		if (event.mouseEvent.isKeyJustPressed(MouseKeys::LeftButton) || 
			event.mouseEvent.isKeyJustPressed(MouseKeys::RightButton))
		{
			currentHistory = HistoryManager::instance->makeVectorMarkHistory();
		}
	}
}

void Tool_Brush::update()
{
	auto * app = ToolsManager::toolsManager->app;
	if (app->activeFile == nullptr) return;
	COORD position = Mouse::instance->position;
	DWORD writen;

	tmp.color = ToolsManager::toolsManager->getPickedColor();
	tmp.znak = ToolsManager::toolsManager->getPickedChar();

	if (app->isMouseOnCanvas(position))
	{
		if (Mouse::instance->isKeyPressed(MouseKeys::LeftButton)){
			Mark * tmpMark = &app->activeFile->marks[position.Y - app->drawingPos.y + app->filePos.y][position.X - app->drawingPos.x + app->filePos.x]; // y / x
			currentHistory->saveMark(tmpMark, *tmpMark);
			*tmpMark = tmp; 
		}
		else if (Mouse::instance->isKeyPressed(MouseKeys::RightButton)){
			Mark * tmpMark = &app->activeFile->marks[position.Y - app->drawingPos.y + app->filePos.y][position.X - app->drawingPos.x + app->filePos.x]; // y / x
			currentHistory->saveMark(tmpMark, *tmpMark);
			*tmpMark = cleer_mark;
		}
	}
}