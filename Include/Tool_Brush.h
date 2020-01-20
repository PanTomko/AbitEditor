#pragma once
#include <BitA.h>
#include "Tool.h"
#include "ToolOption.h"
#include "ToolOptionColor.h"
#include "ToolOptionCharTable.h"
#include "VectorMarkHistory.h"

class Tool_Brush : public Tool
{
public:
	sc::Mark tmp; // change that later
	sc::Mark cleer_mark;

	ToolOptionColor color;
	ToolOptionCharTable wcharTable;
	VectorMarkHistory* currentHistory;

	void input( sc::Event & event ) override;
	void update(float delta) override;

	Tool_Brush();
	~Tool_Brush();
};

