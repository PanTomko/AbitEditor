#pragma once
#include "History.h"
#include <BitA.h>

class MarkHistory : public History
{
public:

	sc::Mark* varr;
	sc::Mark value;

	void reverse() override;


	MarkHistory(sc::Mark* varr, sc::Mark value);
	~MarkHistory();
};

