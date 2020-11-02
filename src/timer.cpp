#include "timer.h"
#include "Arduino.h"

void mikTimer::set_timer(long time, FunctionObject<void(void)>handler, bool repeat) {
    m_budzik = time + millis();
    m_event_handler = handler;
	m_event_is_set = true;
	if (repeat)
		m_repeat = time;
	else
		m_repeat = 0;
}

void mikTimer::stop_timer() {
	 m_event_is_set=false;
	 m_event_handler=nofun;
}

bool mikTimer::is_timer_still_ticking() {
	if(m_event_is_set) {
		return(m_budzik > millis());
	} else {
		return false;
	}
}

void mikTimer::update() {
	if(m_event_is_set) {
		if(m_budzik <= millis()) {
			if (m_repeat)
				m_budzik = millis() + m_repeat;
			else
				m_event_is_set=false;
			m_event_handler();
		}
	}
}

void nofun() {

}
