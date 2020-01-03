#pragma once
#include "History.h"
#include "BitA.h"
#include "Event.h"
#include "VectorMarkHistory.h"

#include <stack>
#include <windows.h>


class HistoryManager {
public:
	HistoryManager(const HistoryManager &) = delete;
	HistoryManager & operator=(const HistoryManager &) = delete;

	static HistoryManager * instance;

	void saveHistory(unsigned short * varr, unsigned short value);
	void saveHistory(wchar_t * varr, wchar_t value);
	void saveHistory(Mark * varr, Mark value);

	VectorMarkHistory* makeVectorMarkHistory();

	void save(History* history);

	void input( Event & event);

	int getID();

private:
	
	std::stack<History*>s_History;
	int ID;

	HistoryManager();
	~HistoryManager();
};


