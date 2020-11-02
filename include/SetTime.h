// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _SetTime_H_
#define _SetTime_H_
#include "Arduino.h"
#include "button_typying_int.h"
//add your includes for the project SetTime here

template<typename char_t>
class TimeSetter {
public:
	using GetTime = FunctionObject<void(uint8_t& sec, uint8_t& min, uint8_t& h)>;
	using SetTime = FunctionObject<void(uint8_t sec, uint8_t min, uint8_t h)>;
	using Bonus = FunctionObject<void()>;

	using DrawLetterAtCallback = FunctionObject<void(ButtonTyper<char_t>&, char_t new_char, uint8_t index)>;
	using DrawAtCallback = FunctionObject<void(char_t new_char, uint8_t index)>;
	TimeSetter(GetTime get, SetTime set,
			DrawLetterAtCallback drawsec, DrawLetterAtCallback drawmin, DrawLetterAtCallback drawh,
			DrawAtCallback draw, DrawAtCallback ont, Bonus apply = 0):m_get_time(get), m_set_time(set), m_draw_at(draw), m_ont(ont), m_apply(apply){
		m_get_time (sec, min, h);
		m_act_mod = 3;
		sttsec.Init(59);
		sttsec.SetCallback_DrawLetterAt(drawsec);
		sttsec.SetNumber(sec);
		sttmin.Init(59);
		sttmin.SetCallback_DrawLetterAt(drawmin);
		sttmin.SetNumber(min);
		stth.Init(23);
		stth.SetCallback_DrawLetterAt(drawh);
		stth.SetNumber(h);
	}

	void Draw_all(){
		m_get_time (sec, min, h);
		Serial.print(sttsec.SetNumber(sec));
		Serial.print(sttmin.SetNumber(min));
		Serial.print(stth.SetNumber(h));
		sttsec.Draw();
		sttmin.Draw();
		stth.Draw();
		m_draw_at(58, 5);
		m_draw_at(58, 8);
	}

	void apply(){
		m_set_time(sttsec.GetNumber(), sttmin.GetNumber(), stth.GetNumber());
		m_get_time(sec, min, h);
		m_ont(h, 3);
		m_ont(min, 6);
		m_ont(sec, 9);
		m_apply();
		m_act_mod = 3;
		sttsec.reset_selection();
		sttmin.reset_selection();
		stth.reset_selection();
	}

	void click(){
		if (m_act_mod == 1){
			sttsec.UpArrowPressed();
		} else if (m_act_mod == 2){
			sttmin.UpArrowPressed();
		} else if (m_act_mod == 3){
			stth.UpArrowPressed();
		} else {
			//ERROR
		}
	}

	void hold(){
		if (m_act_mod == 1 and not sttsec.CurrentPos() == 1){
			sttsec.RightArrowPressed();
		} else if (m_act_mod == 2 and not sttmin.CurrentPos() == 1){
			sttmin.RightArrowPressed();
		} else if (m_act_mod == 3 and not stth.CurrentPos() == 1){
			stth.RightArrowPressed();
		} else if (m_act_mod == 1 and sttsec.CurrentPos() == 1){
			sttsec.RightArrowPressed();
			sttsec.Draw();
//			m_act_mod = 3;
			apply();
		} else if (m_act_mod == 2 and sttmin.CurrentPos() == 1){
			sttmin.RightArrowPressed();
			sttmin.Draw();
			m_act_mod = 1;
		} else if (m_act_mod == 3 and stth.CurrentPos() == 1){
			stth.RightArrowPressed();
			stth.Draw();
			m_act_mod = 2;
		} else {
			//ERROR
		}
	}

	void update(){
		if (m_act_mod == 1){
			update_sec();
		} else if (m_act_mod == 2){
			update_min();
		} else if (m_act_mod == 3){
			update_h();
		} else {
			//ERROR
		}
	}

private:
	ButtonTyperInt sttsec;
	ButtonTyperInt sttmin;
	ButtonTyperInt stth;

	int m_act_mod;//1-sec,2-min,3-h

	GetTime m_get_time;
	SetTime m_set_time;

	Bonus m_apply;

	DrawAtCallback m_draw_at;
	DrawAtCallback m_ont;

	uint8_t sec;
	uint8_t min;
	uint8_t h;

	void update_sec(){
		sttsec.update();
	}
	void update_min(){
		sttmin.update();
	}
	void update_h(){
		stth.update();
	}
};

//Do not add code below this line
#endif /* _SetTime_H_ */
