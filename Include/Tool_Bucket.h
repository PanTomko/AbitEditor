#pragma once
#include "Tool.h"
#include "ToolOptionColor.h"

class Tool_Bucket : public Tool
{
public:

	void input(sc::Event & event) override;
	void update(float delta) override;

	wchar_t picked_char;
	WORD picked_color;
	ToolOptionColor color;

	Tool_Bucket();
	~Tool_Bucket();
};