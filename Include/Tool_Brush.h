#pragma once
#include "BitA.h"
#include "Tool.h"
#include "ToolOption.h"
#include "ToolOptionColor.h"
#include "ToolOptionCharTable.h"
#include "VectorMarkHistory.h"

class Tool_Brush : public Tool
{
public:
	Mark tmp; // change that later
	Mark cleer_mark;

	ToolOptionColor color;
	ToolOptionCharTable wcharTable;
	VectorMarkHistory* currentHistory;

	void input( Event & event ) override;
	void update() override;

	Tool_Brush();
	~Tool_Brush();
};

