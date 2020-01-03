#include "VectorMarkHistory.h"

VectorMarkHistory::VectorMarkHistory() {}

VectorMarkHistory::~VectorMarkHistory() {}

void VectorMarkHistory::saveMark(Mark * varr, Mark value)
{
	v_varr.push_back(varr);
	v_value.push_back(value);
}

void VectorMarkHistory::reverse()
{
	while (!v_varr.empty())
	{
		*v_varr.back() = v_value.back();
		
		v_value.pop_back();
		v_varr.pop_back();
	}
}
