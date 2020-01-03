#pragma once
#include "History.h"
#include "BitA.h"

#include <vector>

class VectorMarkHistory : public History
{
public:

	std::vector<Mark*>v_varr;
	std::vector<Mark>v_value;

	void saveMark(Mark* varr, Mark value);

	void reverse() override;

	VectorMarkHistory();
	~VectorMarkHistory();
};
