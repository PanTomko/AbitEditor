#pragma once
#include "History.h"
#include "BitA.h"

class MarkHistory : public History
{
public:

	Mark* varr;
	Mark value;

	void reverse() override;


	MarkHistory(Mark* varr, Mark value);
	~MarkHistory();
};

