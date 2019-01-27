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

// Thread C++ 14
#include <thread>
#include <chrono>
#include <Winuser.h>

#define WM_COMPLETE (WM_USER + 0)

using namespace std::chrono_literals;

Application::Application()
{
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleInput = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle("BitA Editor");
	window = FindWindow(NULL, "BitA Editor");

	DragAcceptFiles(
		window,
		TRUE
	);

	windowSize = new SMALL_RECT{ 0 , 0 , 120 , 30 };

	SetConsoleScreenBufferSize(consoleOutput, { 120,30 });
	SetConsoleWindowInfo(consoleOutput, TRUE, windowSize);
	SetConsoleMode(consoleInput, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	_setmode(_fileno(stdout), _O_U16TEXT);

	layout.append(L"╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗");
	layout.append(L"║                                                                                                                      ║");
	layout.append(L"╠════════════════════════════════════════════════════════════════════════════════╦═════════════════════════════════════╣");
	layout.append(L"║                                                                                ║                                     ║");
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

	activeFile = nullptr;

	comandLine.app = this;
	toolManadger.app = this;

	running = true;
}

Application::~Application()
{
	delete activeFile; // free file
}

void Application::run()
{
	

	while (running)
	{
		// update / event
		update();

		
		// draw canvas
		drawCanvas();
		toolManadger.draw();
		comandLine.draw(consoleOutput);
		
		// Delay
		//Sleep((1000 / 60));
		std::this_thread::sleep_for(16ms);
	}
}

void Application::update()
{
	//WPARAM wParm;
	//PostMessageW(window, WM_COMPLETE, 0, 0);
	PeekConsoleInputW(
		consoleInput,
		inputBuffer,
		256,
		&ic);

	FlushConsoleInputBuffer(consoleInput);

	for (int i = 0; i < ic; i++)
	{
		toolManadger.update(inputBuffer[i]);

		



		switch (inputBuffer[i].EventType)
		{
			case MOUSE_EVENT:
				//std::wcout << " Mouse " ;
				break;

			case KEY_EVENT:
				comandLine.update(inputBuffer[i].Event.KeyEvent);
				break;

			

			default :
				break;
		}
	}

	//ConsoleInput
	
	ic = 0;
}

void Application::drawLaout()
{
	WriteConsoleOutputCharacterW(
		consoleOutput,
		layout.c_str(),
		120*30,
		{0,0},
		&d);

	WORD tmp = 15;

	SetConsoleCursorPosition(consoleOutput, { 3, 28} );

	d = 0;
}

void Application::drawCanvas()
{
	// max drawable size x = 80 y = 30 - 6 = 24
	// starting pos x = 4 y = 2
	
	if (activeFile == nullptr) return;

	drawingPos = { 2, 4 };

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

	tmp = 15;

	for (int x = 0; x < maxDraw.x; x++)
	{
		wchar_t dd = L'·';

		pos = COORD{ static_cast<short>(drawingPos.x + x), static_cast<short>(drawingPos.y - 1) };
		// output char
		WriteConsoleOutputCharacterW(
			consoleOutput,
			&dd,
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

		pos = COORD{ static_cast<short>(drawingPos.x + x), static_cast<short>(drawingPos.y + maxDraw.y) };
		// output char
		WriteConsoleOutputCharacterW(
			consoleOutput,
			&dd,
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

	for (int y = 0; y < maxDraw.y; y++)
	{
		wchar_t dd = L'·';

		pos = COORD{ static_cast<short>(drawingPos.x - 1), static_cast<short>(drawingPos.y + y ) };
		// output char
		WriteConsoleOutputCharacterW(
			consoleOutput,
			&dd,
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

		pos = COORD{ static_cast<short>(drawingPos.x + maxDraw.x), static_cast<short>(drawingPos.y + y) };
		// output char
		WriteConsoleOutputCharacterW(
			consoleOutput,
			&dd,
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

bool Application::loadBitA(std::wstring path)
{
	BitA * bitAFile;

	delete activeFile;

	std::fstream file(path);

	if(!file.good())
		std::wcout << "HMM" << std::endl;

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

bool Application::isMouseOnCanvas( COORD & mouse_position)
{
	// Testing X
	if (mouse_position.X >= drawingPos.x && mouse_position.X < drawingPos.x + maxDraw.x){
	}
	else return false;

	// Testing Y
	if (mouse_position.Y >= drawingPos.y && mouse_position.Y < drawingPos.y + maxDraw.y){
	}
	else return false;


	return true;
}
