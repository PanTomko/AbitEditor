#pragma once
#include "Tool.h"
class Tool_Picker : public Tool
{
public:

	void update(INPUT_RECORD & record) override;
	wchar_t picked_char;
	WORD picked_color;

	Tool_Picker(ToolsManager * toolManger);
	~Tool_Picker();
};

