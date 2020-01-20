#pragma once
#include "History.h"

#include "VectorMarkHistory.h"

#include <stack>
#include <windows.h>
#include <BitA.h>
#include <Event.h>

class HistoryManager {
public:
	HistoryManager(const HistoryManager &) = delete;
	HistoryManager & operator=(const HistoryManager &) = delete;

	static HistoryManager * instance;

	void saveHistory(unsigned short * varr, unsigned short value);
	void saveHistory(wchar_t * varr, wchar_t value);
	void saveHistory(sc::Mark * varr, sc::Mark value);

	VectorMarkHistory* makeVectorMarkHistory();

	void save(History* history);

	void input( sc::Event & event);

	int getID();

	~HistoryManager();
private:
	
	std::stack<History*>s_History;
	int ID;

	HistoryManager();
};


