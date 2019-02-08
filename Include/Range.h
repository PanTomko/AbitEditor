#pragma once
#include <cstdint> 


class Range {
public:
	long int begin;
	long int end;
	long int on_nr;
	
	long int getNext();
	void reset();

	Range(long int begin = 0, long int end = 0);
	~Range();
};

