#pragma once
#include <string>
#include <windows.h>

class ToolsManager;

class ToolOption
{
public:
	std::wstring name;
	ToolsManager * toolManager;

	virtual void update( INPUT_RECORD & record ) = 0;
	virtual void draw( HANDLE * consoleOutput ) = 0;

	ToolOption( std::wstring name);
	virtual ~ToolOption();
};

