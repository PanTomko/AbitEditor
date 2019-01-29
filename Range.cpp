#include "Range.h"

Range::Range(int begin, int end)
{
	this->begin = begin;
	this->end = end;
	on_nr = begin;
}

Range::~Range()
{
}

int Range::getNext()
{
	if (on_nr + 1 > end)
	{
		return -1;
	}
	on_nr++;
	return on_nr;
}

void Range::reset()
{
	on_nr = begin;
}