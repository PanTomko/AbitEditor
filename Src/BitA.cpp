#include "BitA.h"

BitA::BitA(std::wstring name_path, unsigned int sizeX, unsigned int sizeY)
{
	// create dynamic table

	marks = new Mark *[sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		marks[i] = new Mark[sizeX];
	}

	size_x = sizeX;
	size_y = sizeY;

	path = name_path;

}

BitA::BitA()
{
}

BitA::~BitA()
{
}

void BitA::populate(int znak, short color)
{
	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
		{
			marks[y][x].color = color;
			marks[y][x].znak = znak;
		}
	}
}

bool BitA::save()
{

	std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc); // open and delete text form file

	file << size_x << ' ' << size_y << std::endl; // save size

	// ======================================= save marks
	for (int y = 0; y < size_y; y++)
	{
		for (int x = 0; x < size_x; x++)
		{
			file << static_cast<int>(marks[y][x].color) << ' ' << static_cast<int>(marks[y][x].znak);
			if (x + 1 < size_x) file << ' ';
		}
		file << std::endl;
	}

	file.close();


	return true;
}

bool BitA::load(std::wstring path, unsigned int sizeX, unsigned int sizeY)
{


	return false;
}

Mark::Mark()
{
}

Mark::~Mark()
{
}