#include "Mouse.h"

Mouse * Mouse::instance = new Mouse();

Mouse::Mouse()
{
	keys[MouseKeys::LeftButton] = 0b000u;
	keys[MouseKeys::RightButton] = 0b000u;
	keys[MouseKeys::WeelButton] = 0b000u;
}

Mouse::~Mouse()
{
}

bool Mouse::isKeyPressed(MouseKeys key)
{
	return static_cast<bool>(keys[key] & 0b001);
}
