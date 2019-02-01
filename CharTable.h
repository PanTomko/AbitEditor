#pragma once
#include <vector>
#include <string.h>
#include <windows.h>

#include "Range.h"



class CharTable
{
public:

	std::vector<Range>chars_ranges;
	std::vector<wchar_t>chars;
	std::wstring name;

	void calculateChars();
	bool IsCharacterAvailableInHDC(HDC hdc, wchar_t & character);
	bool IsCharacterAvailableInFont(LPCTSTR szFontName, wchar_t & character);

	CharTable();
	~CharTable();
};

