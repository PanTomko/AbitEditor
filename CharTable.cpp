#include "CharTable.h"

#include <stdio.h>
#include <iostream>

CharTable::CharTable()
{
}

CharTable::~CharTable()
{
}

void CharTable::calculateChars()
{
	//system("cls");
	for (Range & r : chars_ranges) 
	{
		do {
			
			wchar_t tested = (wchar_t)r.on_nr;

			//std::wcout << tested << L", ";
			if (IsCharacterAvailableInFont(TEXT("Consolas"), tested)) chars.push_back(tested);
		} while (r.getNext() != -1);

		chars.push_back(L'\0');
		//system("pause");
	}
	
}

bool CharTable::IsCharacterAvailableInHDC(HDC hdc, wchar_t & character)
{
	WORD indice;

	return (GetGlyphIndicesW(hdc, &character, 1,
		&indice, GGI_MARK_NONEXISTING_GLYPHS) != GDI_ERROR &&
		indice != 0xffff);
}

bool CharTable::IsCharacterAvailableInFont(LPCTSTR szFontName, wchar_t & character)
{
	HDC   hdc;
	HFONT hFontOld;
	HFONT hFontNew;
	bool  bResult;

	/* Create the given font with default parameters. */
	hFontNew = CreateFont(0, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		szFontName);
	if (hFontNew == NULL) return FALSE;

	/* Create a screen compatible DC and select our new font. */
	hdc = GetDC(NULL);
	hFontOld = (HFONT)SelectObject(hdc, hFontNew);

	/* Check if the character is available. */
	bResult = IsCharacterAvailableInHDC(hdc, character);

	/* Cleanup. */
	SelectObject(hdc, hFontOld);
	DeleteObject(hFontNew);
	ReleaseDC(NULL, hdc);

	return bResult;
}