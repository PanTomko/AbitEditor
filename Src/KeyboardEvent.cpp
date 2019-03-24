#include "KeyboardEvent.h"

bool KeyboardEvent::isKey(const Key & key)
{
	return this->key == key;
}

bool KeyboardEvent::isKeyPressed(const Key & key)
{
	return (isKey(key) || key == Key::Null) && static_cast<bool>( keyState & 0b001 );
}

bool KeyboardEvent::isKeyJustRelased(const Key & key)
{
	return (isKey(key) || key == Key::Null) && static_cast<bool>(keyState & 0b010);
}

bool KeyboardEvent::isKeyJustPressed(const Key & key)
{
	return (isKey(key) || key == Key::Null) && static_cast<bool>(keyState & 0b100);
}

KeyboardEvent::KeyboardEvent()
{
}

KeyboardEvent::~KeyboardEvent()
{
}
