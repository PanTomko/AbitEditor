#pragma once
#include <string>
#include <windows.h>
#include <chrono>

#include "BitA.h"
#include "Vector2D.h"
#include "CommandLine.h"
#include "ToolsManager.h"

//{ irInBuf[i].Event.MouseEvent.dwMousePosition.X, irInBuf[i].Event.MouseEvent.dwMousePosition.Y },


class Application
{
public:
	
	HANDLE * consoleOutput; // care it's pointer to a pointer !

	HANDLE consoleOutputBufforOne; // <- C pointer
	HANDLE consoleOutputBufforTwo; // <- C pointer

	HANDLE consoleInput;

	HWND window;
	MSG msg;

	std::chrono::system_clock::time_point t;
	
	CommandLine comandLine;
	ToolsManager toolManadger;

	std::wstring layout;

	DWORD d, ic;
	INPUT_RECORD inputBuffer[1024];
	SMALL_RECT * windowSize;

	Vector2D drawingPos; // position of canvas
	Vector2D maxDraw; // size of canvas

	BitA * activeFile;
	Vector2D filePos;

	void run();

	void update();
	void draw();
	void clean();

	bool running;

	void drawLaout();
	void drawCanvas();

	bool isMouseOnCanvas(COORD & mouse_position);

	bool loadBitA( std::wstring path );
	bool saveBitA();

	Application();
	~Application();
};

