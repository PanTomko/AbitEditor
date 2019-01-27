#pragma once
#include <string>
#include <windows.h>
#include <vector>
#include "ToolOption.h"

class ToolsManager;

class Tool
{
public:

	std::wstring name;
	ToolsManager * toolManager;
	std::vector<ToolOption*>options;

	virtual void update( INPUT_RECORD & record ){};

	Tool( std::wstring name, ToolsManager * toolMan);
	virtual ~Tool();
};

