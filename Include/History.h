#pragma once

class History 
{
public:
	int ID;
	virtual void reverse() = 0;

	History();
	virtual ~History();
};

