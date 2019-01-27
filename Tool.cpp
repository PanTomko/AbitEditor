#include "Tool.h"

Tool::Tool( std::wstring name, ToolsManager * toolMan)
{
	this->name = name;
	this->toolManager = toolMan;
}

Tool::~Tool()
{
}
