#include "WcharHistory.h"

WcharHistory::WcharHistory(wchar_t* varr, wchar_t value)
{
	this->varr = varr;
	this->value = value;
}

WcharHistory::~WcharHistory()
{
	varr = nullptr;
}

void WcharHistory::reverse()
{
	*varr = value;
}