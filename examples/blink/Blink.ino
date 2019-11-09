#include <Arduino.h>
#include "timer.h"
mikTimer t;


void handlerZgas();


void setup() {
	 t.set_timer(1000, handlerZgas);
	 pinMode(13, OUTPUT);
}

void loop() {
	t.update();
}


void handlerZapal() {
	 digitalWrite(13, HIGH);
	 t.set_timer(1000, handlerZgas);
}

void handlerZgas() {
	 digitalWrite(13, LOW);
	 t.set_timer(1000, handlerZapal);
}
