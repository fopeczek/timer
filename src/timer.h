#pragma once
#include "function_objects.h"
#include "Arduino.h"

void nofun();

class mikTimer{
public:
	mikTimer(): m_budzik(0), m_event_handler(nofun), m_event_is_set(false) { }
	void set_timer(long time, FunctionObject<void(void)>);
	void stop_timer();
	bool is_timer_still_ticking();
	void update();
	void setupTimeOutEvent(FunctionObject<void(void)> event_done);
private:
	uint32_t m_budzik;
	FunctionObject<void(void)> m_event_handler;
	bool m_event_is_set;
};
