// Example sketch for interfacing with the DS1302 timekeeping chip.
//
// Copyright (c) 2009, Matt Sparks
// All rights reserved.
//
// http://quadpoint.org/projects/arduino-ds1302
#include"DS1302_driver.h"
//#include <stdio.h>
#include <DS1302.h>
#include "Arduino.h"

int kCePin;
int kIoPin;
int kSclkPin;

DS1302 rtc(5, 6, 7);

DS1302& rtcFactory(int CePin=-1, int IoPin=-1, int SclkPin=-1) {
	static DS1302 rtc(CePin, IoPin, SclkPin);
	kCePin = CePin;
	kIoPin = IoPin;
	kSclkPin = SclkPin;
	return rtc;
}

void setup_pins(int CePin, int IoPin, int SclkPin){
	rtcFactory(CePin, IoPin, SclkPin);
}

void get_time(uint8_t& sec, uint8_t& min, uint8_t& h) {
	  Time t = rtc.time();
	  char buf[50];
	  snprintf(buf, sizeof(buf), "%02d:%02d:%02d",
	           t.hr, t.min, t.sec);

	  // Print the formatted string to serial so we can see the time.
	  Serial.println(buf);
  Serial.print("Time: "); Serial.print(t.hr); Serial.print(":"); Serial.print(t.min); Serial.print(":"); Serial.print(t.sec); Serial.print("\n");
  h = t.hr; min = t.min; sec = t.sec;
}

void set_time(uint8_t sec, uint8_t min, uint8_t h) {
	Time t(2020, 1, 1, h, min, sec, Time::kSunday);
	rtcFactory().time(t);
	Serial.print(sec);
	Serial.print(min);
	Serial.print(h);
	get_time(sec, min, h);
	Serial.print(sec);
	Serial.print(min);
	Serial.print(h);
}

