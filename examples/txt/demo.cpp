#include "demo.h"
#include "button_typying.h"
#include "LiquidCrystal_I2C.h"

ButtonTyper<uint8_t> type;
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void write_char(ButtonTyper<uint8_t>&, uint8_t new_char, uint8_t index) {
	lcd.setCursor(1, index+2);
	lcd.print(new_char);
}

uint8_t* make_alphabet(uint8_t& size) {
	size = 36;
	uint8_t *out = new uint8_t[size];
	int i=0;
	for(;i<26;i++) {
		out[i]=65+i;
	}
	for(;i<36;i++) {
		out[i]=(48-26)+i;
	}
	return out;
}

void setup(){
	lcd.begin(20, 4);
	lcd.backlight();
	lcd.clear();
	uint8_t alphabet_size;
	uint8_t *alphabet = make_alphabet(alphabet_size);
	type.Init(alphabet, alphabet_size, 3, 0, 137);
	type.SetCallback_DrawLetterAt(write_char);
	type.Draw();
}

void loop(){
	type.Update();
}
