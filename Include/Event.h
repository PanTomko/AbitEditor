#pragma once
#include "KeyboardEvent.h"
#include "MouseEvent.h"

class Event
{
public:

	enum class Type {
		Keyboard = 0x0001,
		Mouse = 0x0002
	};

	Type event_type;
	KeyboardEvent keyboardEvent;
	MouseEvent mouseEvent;

	Event();
	~Event();

private:

};

