#pragma once
#include <string>
#include <fstream>

class Mark {
public:
	wchar_t znak;
	short color;
	Mark();
	~Mark();
};

class BitA {
public:

	std::string name;
	std::wstring path;

	int size_x;
	int size_y;

	Mark **marks;

	void populate(int znak, short color);

	bool save();
	bool load(std::wstring path, unsigned int sizeX, unsigned int sizeY);

	BitA(std::wstring name_path, unsigned int sizeX, unsigned int sizeY );
	BitA();
	~BitA();
};

