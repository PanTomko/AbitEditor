#include "Application.h"

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

// TODO :
/*
[x] determin size of render for too big/small .bitA

[x] determin where to draw it

[x] draw mark.chars

[x] create make .bitA file

[ ] add some sort of border or color to distingushe canvas

[x] test difrent size displayes

[x] draw mark.color note. not sure how often we need to do that
but if dont is anyway i can stop worring about asynk

*/

Application::Application()
{
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleInput = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle("BitA Editor");

	windowSize = new SMALL_RECT{ 0 , 0 , 120 , 30 };

	SetConsoleScreenBufferSize(consoleOutput, { 120,30 });
	SetConsoleWindowInfo(consoleOutput, TRUE, windowSize);
	SetConsoleMode(consoleInput, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	_setmode(_fileno(stdout), _O_U16TEXT);

	layout.append(L"╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗");
	layout.append(L"║                                                     Menu                                                             ║");
	layout.append(L"╠════════════════════════════════════════════════════════════════════════════════╦═════════════════════════════════════╣");
	layout.append(L"║                                                                                ║            nav                      ║");
	layout.append(L"║                                                                                ╠═════════════════════════════════════╣");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"║                                                                                ║                                     ║");
	layout.append(L"╠════════════════════════════════════════════════════════════════════════════════╩═════════════════════════════════════╣");
	layout.append(L"║ >                                                                                                                    ║");
	layout.append(L"╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝");

	running = true;
}

Application::~Application()
{
	delete activeFile; // free file
}

void Application::run()
{
	drawLaout();

	while (running)
	{
		// update / event
		update();

		// draw canvas
		drawCanvas();

		// Delay
		Sleep(1000/60);
	}
}

void Application::update()
{
	PeekConsoleInputW(
		consoleInput,
		inputBuffer,
		1,
		&ic);

	for (int i = 0; i < ic; i++)
	{
		switch (inputBuffer[i].EventType)
		{
			case MOUSE_EVENT:
				std::wcout << " Mouse " ;
				break;

			default:
				std::wcout << "       " ;
				break;
		}
	}

	FlushConsoleInputBuffer(consoleInput);
}

void Application::drawLaout()
{
	WriteConsoleOutputCharacterW(
		consoleOutput,
		layout.c_str(),
		120*30,
		{0,0},
		&d);

	SetConsoleCursorPosition(consoleOutput, { 3, 28} );

	d = 0;
}

void Application::drawCanvas()
{
	// max drawable size x = 80 y = 30 - 6 = 24
	// starting pos x = 4 y = 2
	
	Vector2D maxDraw;
	Vector2D drawingPos{ 2, 4 };

	if (activeFile->size_x >= 78) maxDraw.x = 78; 
	else
	{
		maxDraw.x = activeFile->size_x;
		drawingPos.x = static_cast<int>(std::floor( (82 / 2) - (maxDraw.x/2) ));
		
	}

	if (activeFile->size_y >= 22) maxDraw.y = 22;
	else
	{
		maxDraw.y = activeFile->size_y;
		drawingPos.y = static_cast<int>(std::ceil( ( 26/2 ) - ( maxDraw.y/2) )) + 2;
		std::wcout << drawingPos.y;
	}

	WORD tmp = 0;
	COORD pos;
	for (int y = 0; y < maxDraw.y; y++)
	{
		for (int x = 0; x < maxDraw.x; x++)
		{
			pos = COORD{ static_cast<short>(drawingPos.x + x), static_cast<short>(drawingPos.y + y) };
			tmp = activeFile->marks[y + filePos.y][x + filePos.x].color;

			// output char
			WriteConsoleOutputCharacterW(
				consoleOutput,
				&activeFile->marks[y + filePos.y][x + filePos.x].znak,
				1,
				pos,
				&d);
			
			// Add color
			WriteConsoleOutputAttribute(
				consoleOutput,
				&tmp,
				1,
				pos,
				&d);
		}
	}

	SetConsoleCursorPosition(consoleOutput, { 3, 28 });
	
}

bool Application::loadBitA(std::string path)
{
	BitA * bitAFile;

	delete activeFile;

	std::fstream file(path);

	// load size
	int sizeX, sizeY;
	file >> sizeX >> sizeY;

	bitAFile = new BitA(sizeX, sizeY);
	bitAFile->path = path;
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

bool Application::saveBitA()
{
	std::fstream file(activeFile->path, std::ios::in | std::ios::out | std::ios::trunc); // open and delete text form file

	file << activeFile->size_x << ' ' << activeFile->size_y << std::endl; // save size

	// ======================================= save marks
	for (int y = 0; y < activeFile->size_y; y++) 
	{
		for (int x = 0; x < activeFile->size_x; x++)
		{
			file << static_cast<int>(activeFile->marks[y][x].color) << ' ' << static_cast<int>(activeFile->marks[y][x].znak);
			if (x + 1 < activeFile->size_x) file << ' ';
		}
		file << std::endl;
	}

	file.close();

	return false;
}