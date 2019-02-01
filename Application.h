#pragma once
#include "BitA.h"
#include "Vector2D.h"
#include "CommandLine.h"
#include "ToolsManager.h"

#include <string>
#include <windows.h>
#include <chrono>

class Application
{
public:
	
	HANDLE * consoleOutput; // care it's pointer to a pointer 
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

	BitA * activeFile;
	Vector2D filePos;
	Vector2D drawingPos; // position of canvas
	Vector2D maxDraw; // size of canvas

	void run();
	bool running;

	void update();
	void draw();
	void clean();

	void drawLaout();
	void drawCanvas();
	void updateCanvas( const INPUT_RECORD & record);
	bool isMouseOnCanvas(COORD & mouse_position);

	bool loadBitA( std::wstring path );
	
	Application();
	~Application();
};

