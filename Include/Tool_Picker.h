#pragma once
#include "Tool.h"
#include "ToolOptionColor.h"

class Tool_Picker : public Tool
{
public:

	void update(INPUT_RECORD & record) override;
	wchar_t picked_char;
	WORD picked_color;
	ToolOptionColor color;

	Tool_Picker();
	~Tool_Picker();
};

