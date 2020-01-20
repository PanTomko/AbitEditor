#include "HistoryManager.h"

#include "ColorHistory.h"
#include "MarkHistory.h"
#include "WcharHistory.h"

HistoryManager * HistoryManager::instance = new HistoryManager();

HistoryManager::HistoryManager()
{
	ID = 0;
}

HistoryManager::~HistoryManager()
{
}

void HistoryManager::saveHistory(unsigned short * varr, unsigned short value)
{
	ColorHistory * history{ new ColorHistory(varr, value) };
	history->ID = ID;
	save(history);
}

void HistoryManager::saveHistory(wchar_t * varr, wchar_t value)
{
	WcharHistory * history{ new WcharHistory(varr, value) };
	history->ID = ID;
	save(history);
}

void HistoryManager::saveHistory(sc::Mark * varr, sc::Mark value)
{
	MarkHistory * history{ new MarkHistory(varr, value) };
	history->ID = ID;
	save(history);
}

VectorMarkHistory * HistoryManager::makeVectorMarkHistory()
{
	VectorMarkHistory* history = new VectorMarkHistory();
	history->ID = ID;
	save(history);
	return history;
}

void HistoryManager::save(History * history)
{
	s_History.push(history);
}

void HistoryManager::input( sc::Event & event )
{
	if ( event.event_type == sc::Event::Type::Keyboard)
	{
		if (event.keyboardEvent.isKeyJustPressed(sc::Key::Z))
		{	
			if (s_History.empty()) return;

			History * last = s_History.top();
			s_History.pop();

			last->reverse();
			delete last;
		}
	}
}

int HistoryManager::getID()
{
	return ++ID;
}