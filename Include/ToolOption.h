#pragma once
#include "Event.h"

#include <string>
#include <windows.h>

class ToolsManager;

class ToolOption
{
public:
	std::wstring name;

	virtual void input( Event & event ) = 0;
	virtual void update() = 0;
	virtual void draw( HANDLE * consoleOutput ) = 0;

	ToolOption( std::wstring name);
	virtual ~ToolOption();
};

