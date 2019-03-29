#pragma once

#include "Arduino.h"

class mikTimer{
public:
	mikTimer(): m_budzik(0), m_event_handler(0), m_context(0) { }
	void set_timer(long time, void(*)(void *), void* context=0);
	void stop_timer();
	bool is_timer_still_ticking();
	void update();
private:
	uint32_t m_budzik;
	void(*m_event_handler)(void*);
	void * m_context;
};
