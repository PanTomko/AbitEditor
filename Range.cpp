#include "Range.h"

Range::Range(long int begin, long int end)
{
	this->begin = begin;
	this->end = end;
	on_nr = begin;
}

Range::~Range()
{
}

long int Range::getNext()
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