/*#pragma once
#include "BitA.h"
#include "Vector2D.h"
#include "Event.h"
#include "KeyboardEvent.h"

#include <string>
#include <windows.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <queue>


class Application
{
public:
	
	HANDLE * consoleOutput;			// care it's pointer to a pointer 
	HANDLE consoleOutputBufforOne;	// <- C pointer
	HANDLE consoleOutputBufforTwo;	// <- C pointer
	HANDLE consoleInput;

	HWND window;
	MSG msg;

	std::chrono::system_clock::time_point t;
	
	std::wstring layout;

	DWORD d, ic;
	INPUT_RECORD inputBuffer[254];
	SMALL_RECT * windowSize;

	BitA * activeFile;
	Vector2D filePos;		// position of right top corner of active file ( starts drawing form it )
	Vector2D drawingPos;	// position of canvas
	Vector2D maxDraw;		// size of canvas

	bool mouseLeftButtonRelese;

	void run();
	bool running;

	void update();	// Update application
	void draw();	// Draw buffer
	void input();	// proces events
	void clean();	// Clean buffer

	// Events stuff 
	bool poolEvent( Event & _event );				// true if any event was "pooled"
	std::thread thread_input;						// Works with input
	void readInputEvents();							// Reads input in thread_input
	std::queue<Event>evetsBuffer;					// Contains events form thread_input
	std::mutex mutex_evetsBuffer;					// Block acces to evetsBuffer
	
	bool isValidCharacter( const Key & key );		// Check if character hasform by filtring control keys
	std::vector<Key>nonValid;						// Non valid keys

	void drawLaout();
	void drawCanvas();		// Draws activeFile
	void inputCanvas( Event & event );
	bool isMouseOnCanvas(COORD & mouse_position);

	bool loadBitA( std::wstring path );
	
	Application();
	~Application();
};

*/