#include "MouseEvent.h"

MouseEvent::MouseEvent()
{
}

MouseEvent::~MouseEvent()
{
}

bool MouseEvent::isKey(const MouseKeys & key)
{
	return this->key == key;
}

bool MouseEvent::isKeyJustRelased(const MouseKeys & key)
{
	return (isKey(key) || key == MouseKeys::Null) && static_cast<bool>(keyState & 0b010);
}

bool MouseEvent::isKeyJustPressed(const MouseKeys & key)
{
	return (isKey(key) || key == MouseKeys::Null) && static_cast<bool>(keyState & 0b100);
}
