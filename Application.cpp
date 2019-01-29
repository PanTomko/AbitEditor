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
	// Buffor
	consoleOutputBufforOne = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleOutputBufforTwo = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	windowSize = new SMALL_RECT{ 0 , 0 , 120 , 30 };

	SetConsoleScreenBufferSize(consoleOutputBufforOne, { 120,30 });
	SetConsoleWindowInfo(consoleOutputBufforOne, TRUE, windowSize);

	SetConsoleScreenBufferSize(consoleOutputBufforTwo, { 120,30 });
	SetConsoleWindowInfo(consoleOutputBufforTwo, TRUE, windowSize);

	SetConsoleActiveScreenBuffer(consoleOutputBufforOne);	// Making buffor active
	consoleOutput = &consoleOutputBufforTwo;				// Active buffor

	// Input
	consoleInput = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(consoleInput, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	SetConsoleMode(consoleOutputBufforTwo, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	
	// Window related
	_setmode(_fileno(stdout), _O_U16TEXT);
	SetConsoleTitle("BitA Editor");
	window = FindWindow(NULL, "BitA Editor");

	DragAcceptFiles(
		window,
		TRUE
	);

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
	delete activeFile;
}

void Application::run()
{
	while (running)
	{
		//std::this_thread::sleep_for(16ms);
		Sleep(16);
		update();
		clean();
		draw();
	}
}

void Application::update()
{
	PeekConsoleInputW(
		consoleInput,
		inputBuffer,
		1024,
		&ic);

	for (int i = 0; i < ic; i++)
	{
		toolManadger.update(inputBuffer[i]);

		switch (inputBuffer[i].EventType){
			case MOUSE_EVENT:
				break;

			case KEY_EVENT:
				comandLine.update(inputBuffer[i].Event.KeyEvent);
				break;

			default:
				break;
		}
	}
	FlushConsoleInputBuffer(consoleInput);
	ic = 0;
}

void Application::draw()
{
	drawLaout();
	drawCanvas();
	toolManadger.draw();
	comandLine.draw(*consoleOutput);
}

void Application::clean()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	DWORD cellsToWrite;
	DWORD writenChars;
	DWORD writenAtributes;
	WORD clean_color = 15;
	COORD homeCoorde = { 0, 0 };

	// Swaping active screen buffor with buffor we gonna draw to
	
	if (consoleOutput == &consoleOutputBufforOne)
	{
		consoleOutput = &consoleOutputBufforTwo;
		SetConsoleActiveScreenBuffer(consoleOutputBufforOne);
	}
	else
	{
		consoleOutput = &consoleOutputBufforOne;
		SetConsoleActiveScreenBuffer(consoleOutputBufforTwo);
	}
		

	
	// Get info of buffer we need to clean
	if (!GetConsoleScreenBufferInfo(*consoleOutput, &bufferInfo)){
		return;
	}

	cellsToWrite = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;

	FillConsoleOutputCharacterW(
		*consoleOutput,
		L'x',
		cellsToWrite,
		homeCoorde,
		&writenChars
	);

	FillConsoleOutputAttribute(
		*consoleOutput,
		clean_color,
		cellsToWrite,
		homeCoorde,
		&writenAtributes
	);
	//SetConsoleCursorPosition(*consoleOutput, homeCoorde);
	
}

void Application::drawLaout()
{
	WriteConsoleOutputCharacterW(
		*consoleOutput,
		layout.c_str(),
		120*30,
		{0,0},
		&d);

	//SetConsoleCursorPosition(*consoleOutput, { 3, 28} );
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
				*consoleOutput,
				&activeFile->marks[y + filePos.y][x + filePos.x].znak,
				1,
				pos,
				&d);
			
			// Add color
			WriteConsoleOutputAttribute(
				*consoleOutput,
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
			*consoleOutput,
			&dd,
			1,
			pos,
			&d);

		// Add color
		WriteConsoleOutputAttribute(
			*consoleOutput,
			&tmp,
			1,
			pos,
			&d);

		pos = COORD{ static_cast<short>(drawingPos.x + x), static_cast<short>(drawingPos.y + maxDraw.y) };
		// output char
		WriteConsoleOutputCharacterW(
			*consoleOutput,
			&dd,
			1,
			pos,
			&d);

		// Add color
		WriteConsoleOutputAttribute(
			*consoleOutput,
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
			*consoleOutput,
			&dd,
			1,
			pos,
			&d);

		// Add color
		WriteConsoleOutputAttribute(
			*consoleOutput,
			&tmp,
			1,
			pos,
			&d);

		pos = COORD{ static_cast<short>(drawingPos.x + maxDraw.x), static_cast<short>(drawingPos.y + y) };
		// output char
		WriteConsoleOutputCharacterW(
			*consoleOutput,
			&dd,
			1,
			pos,
			&d);

		// Add color
		WriteConsoleOutputAttribute(
			*consoleOutput,
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
