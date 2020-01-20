#pragma once
#include "History.h"

#include <BitA.h>
#include <vector>

class VectorMarkHistory : public History
{
public:

	std::vector<sc::Mark*>v_varr;
	std::vector<sc::Mark>v_value;

	void saveMark(sc::Mark* varr, sc::Mark value);

	void reverse() override;

	VectorMarkHistory();
	~VectorMarkHistory();
};
