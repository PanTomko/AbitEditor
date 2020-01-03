#pragma once
#include "MouseEvent.h"

#include <map>

class Mouse
{
public:

	static Mouse * instance;
	std::map<MouseKeys, unsigned char>keys;

	bool isKeyPressed(MouseKeys key);

	COORD position;

	~Mouse();

private:
	Mouse();
};

