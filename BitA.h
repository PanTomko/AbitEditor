#pragma once
#include <string>

class Mark
{
public:

	wchar_t znak; // wide char lul
	short color; // Is thi microsoft stuf ?

	Mark();
	~Mark();

private:

};


class BitA
{
public:

	std::string name;
	std::string path;

	int size_x;
	int size_y;

	Mark **marks;

	void populate(int znak, short color);

	BitA( unsigned int sizeX, unsigned int sizeY );
	~BitA();
};

