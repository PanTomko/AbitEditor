#pragma once
#include "ToolOption.h"
class ToolOptionColor : public ToolOption
{
public:
	void update() override;
	void input(Event & event) override;
	void draw(HANDLE * consoleOutput) override;

	wchar_t * znak;
	wchar_t default_znak;
	
	WORD picked_color;
	DWORD writen;

	ToolOptionColor();
	~ToolOptionColor();
};

