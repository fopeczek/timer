#include "timer2.h"
#include "Arduino.h"

void mikTimer::set_timer(long time, void (*handler)(void*), void* context) {
    m_budzik = time + millis();
    m_event_handler = handler;
    m_context = context;
}

void mikTimer::stop_timer() {
	 m_event_handler=0;
}

bool mikTimer::is_timer_still_ticking() {
	if(m_event_handler) {
		return(m_budzik > millis());
	} else {
		return false;
	}
}

void mikTimer::update() {
	if(m_event_handler) {
		if(m_budzik <= millis()) {
			void(*event_handler)(void *)  = m_event_handler;
			m_event_handler=0;
			event_handler(m_context);
		}
	}
}
