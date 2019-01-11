#pragma once
#include <string>
#include <windows.h>

#include "BitA.h"
#include "Vector2D.h"

class Application
{
public:
	
	HANDLE consoleOutput;
	HANDLE consoleInput;

	std::wstring layout;

	DWORD d, ic;
	INPUT_RECORD inputBuffer[128];
	SMALL_RECT * windowSize;

	BitA * activeFile;
	Vector2D filePos;

	void run();
	void update();
	// void draw();

	bool running;

	void drawLaout();
	void drawCanvas();

	bool loadBitA( std::string path );
	bool saveBitA();

	Application();
	~Application();
};

