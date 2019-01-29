#pragma once
#include <vector>
#include <string.h>

#include "Range.h"

class CharTable
{
public:

	std::vector<Range>chars_ranges;
	std::wstring name;

	CharTable();
	~CharTable();
};

