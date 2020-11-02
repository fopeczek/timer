// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _button_typying_H_
#define _button_typying_H_
#include "Arduino.h"
#include "timer.h"
#include "function_objects.h"
#include "string"

#include "Streaming.h"
//add your includes for the project button_typying here
template<typename char_t>
class ButtonTyper{
public:
	using DrawLetterAtCallback = FunctionObject<void(ButtonTyper<char_t>&, char_t new_char, uint8_t index)>;
	ButtonTyper():m_alphabets(0), m_alphabet_sizes(0), m_current_string(0) {}
	~ButtonTyper() {
		if (m_current_string) {
			delete[] m_current_string;
		}
	}

	void reset_text(){
		for (int i=0;i<m_text_size;i++){
			set_letter(i, m_default_letter);
		}
	}
	void reset_selection(){
		m_cur_pos = 0;
	}
	void update() {m_timer.update();}
	void LeftArrowPressed() {
		on_blink_on();
		if (m_cur_pos > 0){
			m_cur_pos -= 1;
		}
		on_blink_off();
	}
	uint8_t MaxTextSize() {return m_text_size;}
	void RightArrowPressed() {
		on_blink_on();
		if (m_cur_pos < m_text_size - 1){
			m_cur_pos += 1;
		}else {
			m_cur_pos = 0;
		}
		on_blink_off();
	}
	void UpArrowPressed() {
		set_letter(m_cur_pos, (m_current_string[m_cur_pos]+1) % m_alphabet_sizes[m_cur_pos]);
		on_blink_on();
	}
	void DownArrowPressed() {
		if (m_current_string[m_cur_pos] != 0){
			set_letter(m_cur_pos, m_current_string[m_cur_pos]-1);
		} else {
			set_letter(m_cur_pos, m_alphabet_sizes[m_cur_pos]-1);
		}
		on_blink_on();
	}
	void Draw() {
		for(uint8_t pos = 0; pos<m_text_size; pos++) {
			m_draw_letter_at_callback(*this, m_alphabets[pos][m_current_string[pos]], pos);
		}
	}
	void ResetDisplay() {
		for(uint8_t i = 0;i<=m_text_size;i++){
			m_current_string[i] = m_empty_letter;
		}
	}
	bool SetAlphabetAtPos(const char_t* alphabet, uint8_t alphabet_size, uint8_t letter_pos) { //True means success.
		if(letter_pos < m_text_size){
			m_alphabets[letter_pos] = const_cast<char_t*>(alphabet);
			m_alphabet_sizes[letter_pos] = alphabet_size;
//			Serial<<"m_alphabet_sizes[letter_pos]: "<<m_alphabet_sizes[letter_pos]<<" (a powinno byc: )"<<alphabet_size;Serial.flush();
			return true;
		}
		return false;
	}

	void Init(const char_t* alphabet, uint8_t alphabet_size, uint8_t text_length, char_t empty_letter, uint32_t blink_tm_off=200, uint32_t blink_tm_on=200, char_t default_letter=0) {
		m_alphabets = new char_t*[alphabet_size];
		m_alphabet_sizes = new uint8_t[alphabet_size];
		m_text_size = text_length;
//		Serial<<"step 1\n";Serial.flush();
		for(int letter_pos=0; letter_pos < alphabet_size; letter_pos++) {
//			Serial<<"SetAlphabetAtPos("<<reinterpret_cast<uint32_t>(alphabet)<<", "<<alphabet_size<<", "<<letter_pos<<");";Serial.flush();
//			Serial<<"m_alphabet_sizes[letter_pos]: "<<m_alphabet_sizes[letter_pos];Serial.flush();

			SetAlphabetAtPos(alphabet, alphabet_size, letter_pos);
		}
//		Serial<<"step 2\n";Serial.flush();
		m_blink_off = blink_tm_off;
		m_blink_on = blink_tm_on;
		m_empty_letter = empty_letter;
		m_default_letter = default_letter;
		if (!m_current_string){
			m_current_string = new uint8_t[m_text_size];
		}
//		Serial<<"step 3\n";Serial.flush();
		ResetDisplay();
//		Serial<<"step 4\n";Serial.flush();
		Draw();
//		Serial<<"step 5\n";Serial.flush();
		reset_text();
//		Serial<<"step 6\n";Serial.flush();

		on_blink_off();
//		Serial<<"step 7\n";Serial.flush();
	}
	char_t GetLetter(uint8_t index) {
		return m_alphabets[m_cur_pos][m_current_string[index]];
	}

	uint8_t CurrentPos() {
		return m_cur_pos;
	}

	int GetNumber() {
		return atoi(GetText().c_str());
	}
	String GetText() {
		char* str = new char[m_text_size+1];
		for(int i=0;i<=m_text_size;i++) {
			str[i]=m_alphabets[m_cur_pos][m_current_string[i]];
		}
		str[m_text_size]='\0';
		return String(str);
	}
	bool SetLetter(uint8_t index, uint8_t letter_id) { //True means success
		if (set_letter(index, letter_id)) {
			m_draw_letter_at_callback(*this, m_alphabets[index][letter_id], index);
			return true;
		}
		return false;
	}
	void SetCallback_DrawLetterAt(DrawLetterAtCallback draw_letter_at_callback) {
		m_draw_letter_at_callback = draw_letter_at_callback;
	}
private:
	uint8_t m_cur_pos;
	char_t * *m_alphabets;
	uint32_t m_blink_off;
	uint32_t m_blink_on;
	uint8_t* m_alphabet_sizes;
	uint8_t m_text_size;
	char_t m_default_letter;
	uint8_t * m_current_string;
	char_t m_empty_letter;
	mikTimer m_timer;
	DrawLetterAtCallback m_draw_letter_at_callback;
	void on_blink_on(){
		m_timer.set_timer(m_blink_on, [&](){this->on_blink_off();}, 0);
		m_draw_letter_at_callback(*this, m_alphabets[m_cur_pos][m_current_string[m_cur_pos]], m_cur_pos);
	}
	void on_blink_off(){
		m_timer.set_timer(m_blink_off, [&](){this->on_blink_on();}, 0);
		m_draw_letter_at_callback(*this, m_empty_letter, m_cur_pos);
	}
	bool set_letter(uint8_t index, uint8_t letter_id) { //True means success
		if (index < m_text_size) {
			if (letter_id < m_alphabet_sizes[index]) {
				m_current_string[index] = letter_id;
				return true;
			}
		}
		return false;
	}
};


//Do not add code below this line
#endif /* _button_typying_H_ */
