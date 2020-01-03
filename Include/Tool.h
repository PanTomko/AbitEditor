#pragma once
#include "ToolOption.h"
#include "Event.h"

#include <string>
#include <windows.h>
#include <vector>

class Tool
{
public:

	std::wstring name;
	std::vector<ToolOption*>options;

	virtual void input( Event & event ){};
	virtual void update() {};

	Tool( std::wstring name );
	virtual ~Tool();
};

