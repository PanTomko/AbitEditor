#pragma once
#include "Tool.h"
#include "ToolOption.h"

#include <vector>
#include <windows.h>

class Application;

// singleton
class ToolsManager 
{
	ToolsManager();

public:

	static ToolsManager * toolsManager;
	
	std::vector<Tool*>tools;

	Tool * activeTool;
	ToolOption * activeOption;

	std::wstring menuBuffor;
	std::wstring optionsBuffer;

	Application * app;
	DWORD writen;

	WORD picked_color;
	wchar_t picked_char;
	
	void draw();
	void update(INPUT_RECORD & record );

	ToolsManager(const ToolsManager & tool) = delete;
	~ToolsManager();
};



