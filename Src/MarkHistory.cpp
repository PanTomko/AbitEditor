#include "..\Include\MarkHistory.h"

MarkHistory::MarkHistory(Mark* varr, Mark value)
{
	this->varr = varr;
	this->value = value;
}

MarkHistory::~MarkHistory()
{
	varr = nullptr;
}

void MarkHistory::reverse()
{
	*varr = value;
}

