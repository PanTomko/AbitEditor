/*#include "Application.h"
#include "ToolsManager.h"
#include "CommandLine.h"
#include "HistoryManager.h"
#include "Keyboard.h"
#include "Mouse.h"

// Macro for _setmode
#include <io.h>
#include <fcntl.h>

// file / io 
#include <fstream> 
#include <iostream>
#include <wchar.h>
#include <math.h>

// math stuff | floor/ceil
#include <math.h>

// Thread C++ 14
#include <thread>
#include <chrono>
#include <Winuser.h>

void Application::drawCanvas()
{	
	

	wchar_t dot_char = L'·';
	WORD tmp = 0;
	COORD pos;

	drawingPos = { 2, 4 };

	

	// Drawing dots around canvas
	for (int x = 0; x < maxDraw.x; x++) {
		pos = COORD{ static_cast<short>(drawingPos.x + x), static_cast<short>(drawingPos.y - 1) };
		WriteConsoleOutputCharacterW(*consoleOutput, &dot_char, 1, pos, &d);
		WriteConsoleOutputAttribute(*consoleOutput, &tmp, 1, pos, &d);

		pos = COORD{ static_cast<short>(drawingPos.x + x), static_cast<short>(drawingPos.y + maxDraw.y) };
		WriteConsoleOutputCharacterW(*consoleOutput, &dot_char, 1, pos, &d);
		WriteConsoleOutputAttribute(*consoleOutput, &tmp, 1, pos, &d);
	}

	for (int y = 0; y < maxDraw.y; y++) {
		pos = COORD{ static_cast<short>(drawingPos.x - 1), static_cast<short>(drawingPos.y + y ) };
		WriteConsoleOutputCharacterW(*consoleOutput, &dot_char, 1, pos, &d);
		WriteConsoleOutputAttribute(*consoleOutput, &tmp, 1, pos, &d);

		pos = COORD{ static_cast<short>(drawingPos.x + maxDraw.x), static_cast<short>(drawingPos.y + y) };
		WriteConsoleOutputCharacterW(*consoleOutput, &dot_char, 1, pos, &d);
		WriteConsoleOutputAttribute(*consoleOutput,&tmp, 1, pos, &d);
	}
}

void Application::inputCanvas( Event & event )
{
	if (event.event_type == Event::Type::Keyboard && !CommandLine::instance->active) {

		if (activeFile != nullptr) {
			if (event.keyboardEvent.isKeyPressed(Key::RightArrow) && filePos.x + 1 < activeFile->size_x - maxDraw.x ) {
				filePos.x++;
			}
			
			if (event.keyboardEvent.isKeyPressed(Key::LeftArrow) == 37 && filePos.x - 1 >= 0) {
				filePos.x--;
			}
			
			if (event.keyboardEvent.isKeyPressed(Key::UpArrow) && filePos.y - 1 >= 0) {
				filePos.y--;
			}

			if (event.keyboardEvent.isKeyPressed(Key::DownArrow) == 40 && filePos.y + 1 < activeFile->size_y - maxDraw.y) {
				filePos.y++;
			}
		}
	}
}

bool Application::loadBitA(std::wstring path)
{
	BitA * bitAFile;

	std::fstream file(path);

	if (!file.good())
		return false;

	delete activeFile;

	// load size
	int sizeX, sizeY;
	file >> sizeX >> sizeY;

	bitAFile = new BitA(path, sizeX, sizeY);
	activeFile = bitAFile;

	int color;
	int znak;

	// load marks
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			file >> color >> znak;

			bitAFile->marks[y][x].color = color;
			bitAFile->marks[y][x].znak = znak;
		}
	}

	file.close();

	return false;
}

*/