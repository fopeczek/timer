#include <Arduino.h>
#include "timer.h"

#include <stdlib.h>
//void * operator new(unsigned int n)
//{
//  void * const p = malloc(n);
//  // handle p == 0
//  return p;
//}

void operator delete(void * p, unsigned int)
{
  free(p);
}

mikTimer t;


void handlerZgas();


void setup() {
	 t.set_timer(2000, [](){handlerZapal(2000);});
	 pinMode(13, OUTPUT);
}

void loop() {
	t.update();
}

void handlerZapal(int czas) {
	 digitalWrite(13, HIGH);
	 if (czas > 0)
		 t.set_timer(czas,  [czas](){ handlerZgas(czas);}  );
	 else
		 t.set_timer(-czas,  [czas](){ handlerZgas(czas);}  );
}

void handlerZgas(int czas) {
	 digitalWrite(13, LOW);
	 if(czas < -2000)
		 czas = 2000;
	 else
		 czas -= 100;

	 if (czas > 0)
		 t.set_timer(czas, [czas](){ handlerZapal(czas);} );
	 else
		 t.set_timer(-czas, [czas](){ handlerZapal(czas);} );
}

