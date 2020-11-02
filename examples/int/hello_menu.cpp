// Do not remove the include below
#include "hello_menu.h"
#include "button_typying_int.h"
#include "LiquidCrystal_I2C.h"
#include "click.h"
#include "Streaming.h"

ButtonTyperInt b;
//ButtonTyper<uint8_t> b2;
LiquidCrystal_I2C lcd(0x3F, 20, 4);

Guzik ON_OFF;
Guzik menu_bt;
Guzik encoder;


void hold(){ //hold
	uint32_t ans = b.GetNumber();
	Serial<<"Result: "<<ans;
//	Serial<<"Result: "<<b2.GetText();
}

void set_light(ButtonTyper<uint8_t>&, uint8_t new_char, uint8_t index){
	lcd.setCursor(index+2, 1);
	lcd.print(static_cast<char>( new_char));
}


uint8_t* make_alphabet() {
	uint8_t *m_alphabet = new uint8_t[10];
	uint8_t i=0;
	for(;i<10;i++) {
		m_alphabet[i]=48+i;
	}
	return m_alphabet;
}

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
	b.Init(1234,95,800,800);

//	b2.Init(b.debug_ReturnAlphabet(), 10, 3, 95, 800, 800, 1);
	Serial<<"Hello!";Serial.flush();
//	b2.Init(make_alphabet(), 10, 3, 0, 800, 800, 1);
	lcd.begin();
	lcd.backlight();
	lcd.clear();
	b.SetCallback_DrawLetterAt(set_light);
//	b2.SetCallback_DrawLetterAt(set_light);

	ON_OFF.setupClickHandler([](){b.DownArrowPressed();});
	ON_OFF.setupUsingAnalogPin(A0);
	ON_OFF.setupHoldHandler([](){b.LeftArrowPressed();});

	menu_bt.setupClickHandler([](){b.UpArrowPressed();});
	menu_bt.setupUsingAnalogPin(A2);
	menu_bt.setupHoldHandler([](){b.RightArrowPressed();});

	encoder.setupClickHandler(hold);
	encoder.setupUsingDigitalPin(12);
	b.Draw();
//	b2.Draw();

//	encoder.setupHoldHandler(menu_hold);
	Serial<<"Po setup";Serial.flush();
}

// The loop function is called in an endless loop
void loop()
{
	b.update();
//	b2.update();
	ON_OFF.update();
	menu_bt.update();
	encoder.update();
//Add your repeated code here
}
