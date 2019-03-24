#pragma once
#include "KeyboardEvent.h"
#include <map>
#include <bitset>

class Keyboard
{
public:

	static Keyboard * instance;
	std::map<Key, unsigned char>keys;

	//bool isKeyPressed();
	//bool isKeyJustsPressed();
	//bool isKeyJustRelased();
	
	~Keyboard();
private:

	Keyboard();
	
};

