#pragma once
#include "BitA.h"
#include "Tool.h"
#include "ToolOption.h"
#include "ToolOptionColor.h"
#include "ToolOptionCharTable.h"

class Tool_Brush : public Tool
{
public:
	Mark tmp; // change that later
	Mark cleer_mark;

	ToolOptionColor color;
	ToolOptionCharTable wcharTable;

	void update(INPUT_RECORD & record);

	Tool_Brush(ToolsManager * toolManger);
	~Tool_Brush();
};

