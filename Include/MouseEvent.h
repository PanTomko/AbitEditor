#pragma once
#include <windows.h>

// Events for mouse dont work for repetinh/holding buttons !

enum class MouseKeys {
	Null = 0x0000,
	LeftButton = 0x0001,
	RightButton = 0x0002,
	WeelButton = 0x0004
};

class MouseEvent
{
public:

	unsigned char keyState; // just_pressed/just_relased/pressed
	MouseKeys key;
	COORD position;

	bool isKey(const MouseKeys & key);
	bool isKeyJustRelased(const MouseKeys & key);
	bool isKeyJustPressed(const MouseKeys & key);

	MouseEvent();
	~MouseEvent();
};

