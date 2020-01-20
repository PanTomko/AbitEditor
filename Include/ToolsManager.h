#pragma once
#include "Tool.h"
#include "ToolOption.h"

#include <Vector2D.h>
#include <vector>
#include <windows.h>
#include <Console.h>

class SceneApp;

// singleton
class ToolsManager 
{
public:
	~ToolsManager();
	ToolsManager(const ToolsManager & tool) = delete;
	static ToolsManager * toolsManager;
	SceneApp * app;

	unsigned short getPickedColor();
	wchar_t getPickedChar();

	void setPickedColor(const unsigned short & color);
	void setPickedChar(const wchar_t & wchar);

	void draw(sc::Console & console);
	void input(sc::Event & event);
	void update(float delta);

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

	sc::Vector2D mouse_position_RTC; // Relative to canvas

	ToolsManager();
};



