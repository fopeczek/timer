#include "timer.h"
timerContext c;


void handlerZgas(void *);


void setup() {
	 set_timer(&c, 1000, handlerZgas);
	 pinMode(13, OUTPUT);
}

void loop() {
	update_timer(&c );
}


void handlerZapal(void *) {
	 digitalWrite(13, HIGH);
	 set_timer(&c, 1000, handlerZgas);
}

void handlerZgas(void *) {
	 digitalWrite(13, LOW);
	 set_timer(&c, 1000, handlerZapal);
}
