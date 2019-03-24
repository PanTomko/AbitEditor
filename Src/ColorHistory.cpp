#include "ColorHistory.h"

ColorHistory::ColorHistory(unsigned short * varr, unsigned short value)
{
	this->varr = varr;
	this->value = value;
}

ColorHistory::~ColorHistory()
{
	varr = nullptr;
}

void ColorHistory::reverse()
{
	*varr = value;
}