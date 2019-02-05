#pragma once
#include "ToolOption.h"

#include <string>
#include <windows.h>
#include <vector>

class Tool
{
public:

	std::wstring name;
	std::vector<ToolOption*>options;

	virtual void update( INPUT_RECORD & record ){};

	Tool( std::wstring name );
	virtual ~Tool();
};

