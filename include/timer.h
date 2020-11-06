#pragma once
#include "function_objects.h"
#include "Arduino.h"


class mikTimer{
public:
	mikTimer(): m_budzik(0), m_event_handler(nofun), m_event_is_set(false), m_repeat(0) { }
	void set_timer(long time, FunctionObject<void(void)>, bool repeat = false);
	void stop_timer();
	bool is_timer_still_ticking();
	uint32_t how_much_to_wait() {return max(0,m_budzik - millis());}
	void update();
private:
	static void nofun(){}
	uint32_t m_budzik;
	FunctionObject<void(void)> m_event_handler;
	bool m_event_is_set;
	uint32_t m_repeat; //timer lenght to repeat.
};
