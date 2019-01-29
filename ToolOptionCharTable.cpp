#include "ToolOptionCharTable.h"
#include "utf.h"
#include <iostream>

ToolOptionCharTable::ToolOptionCharTable() : ToolOption( L" Style " )
{
	// Ini char tables
	lettersTable.chars_ranges.push_back(Range{ 0x2660, 0x2736 });
	lettersTable.name = L"letters";

	activeCharTable = &lettersTable;
}

ToolOptionCharTable::~ToolOptionCharTable()
{
}

void ToolOptionCharTable::draw(HANDLE * consoleOutput)
{
	/*
	// add 83 to get start pos
	COORD startPos = { 84, 5 };
	COORD drawPos = { 0, 0 };
	WORD color = 15;
	//LPINT lpint;

	for (auto & i : activeCharTable->chars_ranges)
	{
		wchar_t tmp_char = 0x2660;
		while (i.getNext() != -1)
		{
			tmp_char = i.on_nr;
			std::
			if (utf::is_valid(tmp_char))
			{
				Write*consoleOutputCharacterW(
					*consoleOutput,
					&tmp_char,
					1,
					{ startPos.X + drawPos.X, startPos.Y + drawPos.Y },
					&writen);

				Write*consoleOutputAttribute(
					*consoleOutput,
					&color,
					1,
					{ startPos.X + drawPos.X, startPos.Y + drawPos.Y },
					&writen
				);

				drawPos.X += 1;
				if (drawPos.X > 32)
				{
					drawPos.X = 0;
					drawPos.Y += 1;
				}
			}
		}

		i.reset();
	}

	*/

	/*for (short y = 0; y < 16; y += 2)
	{
		for (short x = 0; x < 32; x += 1)
		{
			if (x >= 16)
				space = 1;
			else
				space = 0;

			while (IsTextUnicode(&show_znak, 1, NULL))
			{
				show_znak++;
			}

			Write*consoleOutputCharacterW(
				*consoleOutput,
				&show_znak,
				1,
				{ startPos.X + x + space, startPos.Y + y },
				&writen);

			Write*consoleOutputAttribute(
				*consoleOutput,
				&color,
				1,
				{ startPos.X + x + space, startPos.Y + y },
				&writen
			);

			show_znak++;
		}
	}*/
}

void ToolOptionCharTable::update(INPUT_RECORD & record)
{
}