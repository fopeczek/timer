// Do not remove the include below
#include "SetTime.h"
#include "example.h"
#include "Time.h"
#include "LiquidCrystal_I2C.h"
#include <stdio.h>
#include "click.h"
#include "DS1302_driver.h"

void draw_at(ButtonTyper<uint8_t>&, uint8_t new_char, uint8_t index);
void draw_ate(uint8_t new_char, uint8_t index);
void set_time(uint8_t sec, uint8_t min, uint8_t h);
void get_time(uint8_t& sec, uint8_t& min, uint8_t& h);
void onetoone(uint8_t new_char, uint8_t index);

//GetTime get, SetTime set, DrawLetterAtCallback drawsec, DrawLetterAtCallback drawmin, DrawLetterAtCallback drawh, DrawLetterAtCallback draw
TimeSetter<uint8_t>& give_time_set(){
	static TimeSetter<uint8_t> time_set(
			get_time,
			set_time,
			[](ButtonTyper<uint8_t>& b, uint8_t new_char, uint8_t index) {draw_at(b, new_char, index+9);},
			[](ButtonTyper<uint8_t>& b, uint8_t new_char, uint8_t index) {draw_at(b, new_char, index+6);},
			[](ButtonTyper<uint8_t>& b, uint8_t new_char, uint8_t index) {draw_at(b, new_char, index+3);},
			draw_ate, onetoone);
	return time_set;
}


LiquidCrystal_I2C lcd(0x3F, 20, 4);

Guzik one;

void draw_ate(uint8_t new_char, uint8_t index){
	lcd.setCursor(index, 1);
	lcd.print(static_cast<char>( new_char));
}

void onetoone(uint8_t new_char, uint8_t index){
	lcd.setCursor(index, 2);
	lcd.print(new_char);
}

void draw_at(ButtonTyper<uint8_t>&, uint8_t new_char, uint8_t index){
	lcd.setCursor(index, 1);
	lcd.print(static_cast<char>( new_char));
}

void click(){
	give_time_set().click();
}

void hold(){
	give_time_set().hold();
}

void setup() {
	Serial.begin(9600);
	lcd.begin();
	lcd.backlight();
	lcd.clear();
	one.setupUsingAnalogPin(A0);
	one.setupClickHandler(click);
	one.setupHoldHandler(hold);
	give_time_set().Draw_all();
	setup_pins(5, 6, 7);
}

void loop() {
	give_time_set().update();
 	one.update();
}
