#pragma once
#include "Tool.h"
#include "ToolOption.h"
#include "Vector2D.h"

#include <vector>
#include <windows.h>

class Application;

// singleton
class ToolsManager 
{
public:
	~ToolsManager();
	ToolsManager(const ToolsManager & tool) = delete;
	static ToolsManager * toolsManager;
	Application * app;

	unsigned short getPickedColor();
	wchar_t getPickedChar();

	void setPickedColor(const unsigned short & color);
	void setPickedChar(const wchar_t & wchar);

	void draw();
	void update(INPUT_RECORD & record);

private:
	std::vector<Tool*>tools;
	Tool * activeTool;
	ToolOption * activeOption;

	unsigned short picked_color;
	wchar_t picked_char;

	std::wstring menuBuffor;
	std::wstring optionsBuffer;

	bool show_xy;
	unsigned long writen;

	Vector2D mouse_position_RTC; // Relative to canvas

	ToolsManager();
};



