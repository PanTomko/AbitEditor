#pragma once
class Range {
public:
	int begin;
	int end;
	int on_nr;

	int getNext();
	void reset();

	Range(int begin = 0, int end = 0);
	~Range();
};

