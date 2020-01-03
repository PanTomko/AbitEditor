﻿#include "Application.h"
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
	SetConsoleMode(consoleOutputBufforOne, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	
	// Window related
	_setmode(_fileno(stdout), _O_U16TEXT);
	SetConsoleTitle("BitA Editor");
	window = FindWindow(NULL, "BitA Editor");

	DragAcceptFiles(
		window,
		TRUE
	);

	// Layout crations
	{
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
	}
	
	// Ini
	activeFile = nullptr;

	CommandLine::instance->app = this;
	ToolsManager::toolsManager->app = this;

	running = true;

	// non valid chars 
	nonValid = { Key::Alt, Key::Shift, Key::Ctrl, Key::Backspace,
							 Key::CapsLock, Key::Clear, Key::Delete, Key::Enter,
							 Key::DownArrow, Key::RightArrow, Key::LeftArrow, Key::UpArrow,
							 Key::Escape, Key::Help, Key::Home, Key::Tab, Key::Insert,
							 Key::PrintSreen, Key::PageDown, Key::PageUP };
}

Application::~Application()
{
	delete activeFile;
}

inline std::wstring convert(const std::string& as)
{
	// deal with trivial case of empty string
	if (as.empty())    return std::wstring();

	// determine required length of new string
	size_t reqLength = ::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), 0, 0);

	// construct new string of required length
	std::wstring ret(reqLength, L'\0');

	// convert old string to new string
	::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), &ret[0], (int)ret.length());

	// return new string ( compiler should optimize this away )
	return ret;
}

void Application::run()
{
	thread_input = std::thread(&Application::readInputEvents); // Start accumulating events !

	while (running)
	{
		std::this_thread::sleep_for(16ms);

		input();
		update();

		clean();
		draw();
	}
}

void Application::update()
{
	ToolsManager::toolsManager->update();
}

void Application::draw()
{
	drawLaout();
	drawCanvas();
	ToolsManager::toolsManager->draw();
	CommandLine::instance->draw(*consoleOutput);
}

void Application::input()
{
	Event _event;

	while (poolEvent(_event))
	{
		CommandLine::instance->input(_event);
		ToolsManager::toolsManager->input(_event);
		if (!CommandLine::instance->active) HistoryManager::instance->input(_event);
		inputCanvas(_event);
	}
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
		L' ',
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
}

bool Application::poolEvent(Event & _event)
{
	std::lock_guard<std::mutex> lock(mutex_evetsBuffer);

	if (!evetsBuffer.empty())
	{
		_event = evetsBuffer.front();
		evetsBuffer.pop();
		return true;
	}

	return false;
}

void Application::readInputEvents()
{
	while (true)
	{
		ReadConsoleInputW(
			consoleInput,
			inputBuffer,
			254,
			&ic);

		mutex_evetsBuffer.lock();
		for (unsigned int i = 0; i < ic; i++)
		{
			Event _event;

			switch (inputBuffer[i].EventType)
			{
				case KEY_EVENT:
				{
					_event.event_type = Event::Type::Keyboard;
					_event.keyboardEvent.key = static_cast<Key>(inputBuffer[i].Event.KeyEvent.wVirtualKeyCode);
					_event.keyboardEvent.repeatCount = inputBuffer[i].Event.KeyEvent.wRepeatCount;

					wchar_t tmpWCT = inputBuffer[i].Event.KeyEvent.uChar.UnicodeChar;
					_event.keyboardEvent.unicode = isValidCharacter(_event.keyboardEvent.key) ? tmpWCT : L'\0';

					if (Keyboard::instance->keys.find(_event.keyboardEvent.key) == Keyboard::instance->keys.end()) {
						Keyboard::instance->keys[_event.keyboardEvent.key] = 0b000u; // Key not found so make one
					}

					if (inputBuffer[i].Event.KeyEvent.bKeyDown)
					{
						if (!bool(Keyboard::instance->keys[_event.keyboardEvent.key] & 0b001)) {
							Keyboard::instance->keys[_event.keyboardEvent.key] |= 0b101;
						}
					}
					else
					{
						Keyboard::instance->keys[_event.keyboardEvent.key] &= ~(1UL << 0);
						Keyboard::instance->keys[_event.keyboardEvent.key] |= 0b010;
					}

					_event.keyboardEvent.keyState = Keyboard::instance->keys[_event.keyboardEvent.key];
					evetsBuffer.push(_event);

					if (Keyboard::instance->keys[_event.keyboardEvent.key] & 0b010) {
						Keyboard::instance->keys[_event.keyboardEvent.key] &= ~(1UL << 1);
					}

					if (Keyboard::instance->keys[_event.keyboardEvent.key] & 0b100) {
						Keyboard::instance->keys[_event.keyboardEvent.key] &= ~(1UL << 2);
					}

				}
				break;

				case MOUSE_EVENT:
				{
					_event.event_type = Event::Type::Mouse;
					_event.mouseEvent.position = inputBuffer[i].Event.MouseEvent.dwMousePosition;
					Mouse::instance->position = inputBuffer[i].Event.MouseEvent.dwMousePosition;
					_event.mouseEvent.key = MouseKeys::Null;

					std::bitset<3>set = inputBuffer[i].Event.MouseEvent.dwButtonState;
					
					for (auto & j : Mouse::instance->keys) {

						std::bitset<3>testedKey = static_cast<unsigned int>(j.first);
						std::bitset<3>testedKeyStatus = static_cast<unsigned int>(j.second);

						if (set.to_ulong() & testedKey.to_ulong()) {
							
							if (testedKeyStatus[0] == 0)
							{
								testedKeyStatus[2] = 1;

								_event.mouseEvent.keyState = testedKeyStatus.to_ulong();
								_event.mouseEvent.key = j.first;
								j.second = testedKeyStatus.to_ulong();
								evetsBuffer.push(_event);
								
								testedKeyStatus[2] = 0;
							}

							testedKeyStatus[0] = 1;
							
						}
						else {
							if (testedKeyStatus[0] == 1)
							{
								testedKeyStatus[1] = 1;

								_event.mouseEvent.keyState = testedKeyStatus.to_ulong();
								_event.mouseEvent.key = j.first;
								j.second = testedKeyStatus.to_ulong();
								evetsBuffer.push(_event);
								
								testedKeyStatus[1] = 0;
							}

							testedKeyStatus[0] = 0;
						}
						j.second = testedKeyStatus.to_ulong(); // save mouse status in Mouse::instance
					}
				}
				break;
			}
		}
		mutex_evetsBuffer.unlock();
	}
}

bool Application::isValidCharacter(const Key & key)
{

	for (auto & i : nonValid)
	{
		if (key == i) {
			return false;
		}
	}

	return true;
}

void Application::drawLaout()
{
	WriteConsoleOutputCharacterW(
		*consoleOutput,
		layout.c_str(),
		120*30,
		{0,0},
		&d);
}

void Application::drawCanvas()
{	
	if (activeFile == nullptr) return;

	wchar_t dot_char = L'·';
	WORD tmp = 0;
	COORD pos;

	drawingPos = { 2, 4 };

	// Calculating starting pos and size of drawing
	if (activeFile->size_x >= 78) maxDraw.x = 78; 
	else {
		maxDraw.x = activeFile->size_x;
		drawingPos.x = static_cast<int>(std::floor( (82 / 2) - (maxDraw.x/2) ));
	}

	if (activeFile->size_y >= 22) maxDraw.y = 22;
	else {
		maxDraw.y = activeFile->size_y;
		drawingPos.y = static_cast<int>(std::ceil( ( 26/2 ) - ( maxDraw.y/2) )) + 2;
	}

	// Drawing image form active file
	for (int y = 0; y < maxDraw.y; y++)
	{
		for (int x = 0; x < maxDraw.x; x++)
		{
			pos = COORD{ static_cast<short>(drawingPos.x + x), static_cast<short>(drawingPos.y + y) };
			tmp = activeFile->marks[y + filePos.y][x + filePos.x].color;

			WriteConsoleOutputCharacterW(
				*consoleOutput,
				&activeFile->marks[y + filePos.y][x + filePos.x].znak,
				1,
				pos,
				&d);
			
			WriteConsoleOutputAttribute(*consoleOutput,&tmp,1,pos,&d);
		}
	}

	tmp = 15;

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
