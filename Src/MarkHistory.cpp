#include "MarkHistory.h"

MarkHistory::MarkHistory(sc::Mark* varr, sc::Mark value)
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

