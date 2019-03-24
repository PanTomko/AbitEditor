#pragma once
#include "History.h"
class WcharHistory : public History
{
public:

	wchar_t* varr;
	wchar_t value;

	void reverse() override;

	WcharHistory(wchar_t* varr, wchar_t value);
	~WcharHistory();
};

