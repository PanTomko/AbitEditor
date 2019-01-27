#pragma once
#include <vector>
#include <windows.h>

#include "Tool.h"
#include "ToolOption.h"

class Application;

class ToolsManager
{
public:

	std::vector<Tool*>tools;
	//std::vector<ToolOption*>options;

	Tool * activeTool;
	ToolOption * activeOption;

	std::wstring menuBuffor;
	std::wstring optionsBuffer;

	Application * app;
	DWORD writen;
	
	void draw();
	void update(INPUT_RECORD & record );

	ToolsManager();
	~ToolsManager();
};

