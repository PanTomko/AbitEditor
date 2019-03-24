#pragma once

enum class ControlKey {
	Null		= 0x0000,
	Shift		= 0x0010, // SHIFT_PRESSED
	Numlock		= 0x0020, // NUMLOCK_ON
	Capslock	= 0x0080, // CAPSLOCK_ON
	ScrollLock	= 0x0040, // SCROLLLOCK_ON
	Enhanced	= 0x0100, // ENHANCED_KEY
	LeftAlt		= 0x0002, // LEFT_ALT_PRESSED
	RightAlt	= 0x0001, // RIGHT_ALT_PRESSED
	LeftCtrl	= 0x0008, // LEFT_CTRL_PRESSED
	RightCtrl	= 0x0004  // RIGHT_CTRL_PRESSED
};

enum class Key {
	Null		= 0x00,
	Undefined	= 0x07,
	Backspace	= 0x08,
	Tab			= 0x09,
	Clear		= 0x0C,
	Enter		= 0x0D,
	Shift		= 0x10,
	Ctrl		= 0x11,
	Alt			= 0x12,
	Pause		= 0x13,
	CapsLock	= 0x14,
	Kana		= 0x15,
	Escape		= 0x1B,
	Space		= 0x20,	// VK_SPACE
	PageUP		= 0x21,	// VK_PRIOR
	PageDown	= 0x22, // VK_NEXT
	End			= 0x23, // VK_END
	Home		= 0x24, // VK_HOME
	LeftArrow	= 0x25, // VK_LEFT
	UpArrow		= 0x26, // VK_UP
	RightArrow	= 0x27, // VK_RIGHT
	DownArrow	= 0x28, // VK_DOWN
	Select		= 0x29, // VK_SELECT
	Print		= 0x2A, // VK_PRINT
	PrintSreen	= 0x2C, // VK_SNAPSHOT
	Insert		= 0x2D, // VK_INSERT
	Delete		= 0x2E, // VK_DELETE
	Help		= 0x2F, // VK_HELP
	Num0		= 0x30, // (key 0)
	Num1		= 0x31, // (key 1)
	Num2		= 0x32, // (key 2)
	Num3		= 0x33, // (key 3)
	Num4		= 0x34, // (key 4)
	Num5		= 0x35, // (key 5)
	Num6		= 0x36, // (key 6)
	Num7		= 0x37, // (key 7)
	Num8		= 0x38, // (key 8)
	Num9		= 0x39, // (key 9)
	A			= 0x41,
	B			= 0x42,
	C			= 0x43,
	D			= 0x44,
	E			= 0x45,
	F			= 0x46,
	G			= 0x47,
	H			= 0x48,
	I			= 0x49,
	J			= 0x4A,
	K			= 0x4B,
	L			= 0x4C,
	M			= 0x4D,
	N			= 0x4E,
	O			= 0x4F,
	P			= 0x50,
	Q			= 0x51,
	R			= 0x52,
	S			= 0x53,
	T			= 0x54,
	U			= 0x55,
	V			= 0x56,
	W			= 0x57,
	X			= 0x58,
	Y			= 0x59,
	Z			= 0x5A,
	LShift		= 0xA0,
	RShift		= 0xA1
};

enum class KeyStates {
	Pressed = 0b001,
	JustPressed = 0b010,
	JustRelesed = 0b100
};

class KeyboardEvent
{
public:

	Key key;
	unsigned char keyState; // just_pressed/just_relased/pressed

	unsigned int repeatCount;
	wchar_t unicode;

	bool isKey(const Key & key);
	bool isKeyPressed(const Key & key);
	bool isKeyJustRelased(const Key & key);
	bool isKeyJustPressed(const Key & key);

	KeyboardEvent();
	~KeyboardEvent();
};

