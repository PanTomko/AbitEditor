#pragma once
#include "ToolOption.h"
#include "CharTable.h"

class ToolOptionCharTable : public ToolOption
{
public:

	void draw(HANDLE * consoleOutput) override;
	void update(INPUT_RECORD & record) override;

	DWORD writen;

	wchar_t char_to_use;
	CharTable * activeCharTable;
	std::vector<CharTable*>charTables;

	int menu_position;

	CharTable commonTable;
	CharTable specialTable;
	CharTable extraTable;
	CharTable smallDots;

	ToolOptionCharTable();
	~ToolOptionCharTable();
};

