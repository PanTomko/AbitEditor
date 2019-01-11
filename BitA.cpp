#include "BitA.h"

BitA::BitA( unsigned int sizeX, unsigned int sizeY )
{
	// create dynamic table

	marks = new Mark * [sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		marks[i] = new Mark[sizeX];
	}

	size_x = sizeX;
	size_y = sizeY;
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

Mark::Mark()
{
}

Mark::~Mark()
{
}