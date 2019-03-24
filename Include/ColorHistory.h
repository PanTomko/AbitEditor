#pragma once
#include "History.h"
class ColorHistory : public History
{
public:

	unsigned short * varr;
	unsigned short value;

	void reverse() override;

	ColorHistory(unsigned short * varr, unsigned short value);
	~ColorHistory();
};

