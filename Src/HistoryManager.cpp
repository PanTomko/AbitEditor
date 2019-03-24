#include "HistoryManager.h"

#include "ColorHistory.h"
#include "MarkHistory.h"
#include "WcharHistory.h"

HistoryManager * HistoryManager::instance = new HistoryManager();

HistoryManager::HistoryManager()
{
	ID = 0;
	zJustPressed = false;
	zPressed = false;
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

void HistoryManager::saveHistory(Mark * varr, Mark value)
{
	MarkHistory * history{ new MarkHistory(varr, value) };
	history->ID = ID;
	save(history);
}

void HistoryManager::save(History * history)
{
	s_History.push(history);
}

void HistoryManager::update(const INPUT_RECORD & record)
{
	if (s_History.empty()) return;

	if	(record.EventType == KEY_EVENT )
	{

		if (record.Event.KeyEvent.wVirtualKeyCode == L'Z')
		{
			zJustPressed = false;

			if (record.Event.KeyEvent.bKeyDown == true && zPressed == false)
			{
				zJustPressed = true;
				zPressed = true;
			}

			if (record.Event.KeyEvent.bKeyDown == false && zPressed == true) zPressed = false;
		}

		if (zJustPressed == true)
		{
			
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