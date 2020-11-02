//Class that allows typing in any integer from 0 to max number.
#pragma once
#include "button_typying.h"
#include "Streaming.h"

//add your includes for the project button_typying here
class ButtonTyperInt {
public:
	ButtonTyperInt() {}
	~ButtonTyperInt() {
		delete[] m_alphabet;
	}

	void reset_text(){
		m_button_typer.reset_text();
	}

	void reset_selection(){
		m_button_typer.reset_selection();
	}
	void update() {m_button_typer.update();}
	void LeftArrowPressed()  {
		uint8_t cur_digit = m_button_typer.GetLetter(m_button_typer.CurrentPos());
		if (cur_digit > m_cur_digit_bak)
			validate_whole_number();
		m_button_typer.LeftArrowPressed();
		m_cur_digit_bak = m_button_typer.GetLetter(m_button_typer.CurrentPos());
	}
	void RightArrowPressed() {
		uint8_t cur_digit = m_button_typer.GetLetter(m_button_typer.CurrentPos());
		if (cur_digit > m_cur_digit_bak)
			validate_whole_number();

		m_button_typer.RightArrowPressed();
		set_alphabet_on_curpos();

		m_cur_digit_bak = m_button_typer.GetLetter(m_button_typer.CurrentPos());
	}
	void UpArrowPressed() {
		m_button_typer.UpArrowPressed();
	}
	void DownArrowPressed() {
		m_button_typer.DownArrowPressed();
	}
	void Draw() {
		m_button_typer.Draw();
	}
	void ResetDisplay() {
		m_button_typer.ResetDisplay();
	}

	void Init(uint32_t max_number, uint8_t empty_letter=95, uint32_t blink_tm_off=800, uint32_t blink_tm_on=800) {
		make_alphabet();
		m_max_number = max_number;
		count_max_value_chars();
		uint8_t text_length;
		if (max_number == 0)
			text_length = 1;
		else
			text_length = uint32_t(log10(float(max_number)))+1;

		m_button_typer.Init(m_alphabet, 10, text_length, empty_letter, blink_tm_off, blink_tm_on);
		set_alphabet_on_curpos();
		m_cur_digit_bak = m_button_typer.GetLetter(m_button_typer.CurrentPos());
	}

	int GetNumber() {
		validate_whole_number();
		return atoi(GetText().c_str());
	}

	String GetText() {
		validate_whole_number();
		return m_button_typer.GetText();
	}

	uint8_t CurrentPos() {
		return m_button_typer.CurrentPos();
	}

	bool SetNumber(uint32_t number) { //True means success
		if (number <= m_max_number) {
			char* bufor = new char[10];
			itoa(number, bufor, 10);
			int digit_count = 0;
			for(digit_count=0;bufor[digit_count];digit_count++) {}


			//Setting trailing zeros.
			int pos=0;
			for(;pos < m_button_typer.MaxTextSize() - digit_count;pos++) {
				m_button_typer.SetLetter(pos, 0);
//				Serial<<"Writing 0 at " << pos << "\n";
			}


			//Setting remaining digits
			for(int pos2=0;bufor[pos2];pos2++) {
				m_button_typer.SetLetter(pos + pos2, bufor[pos2]-48);
//				Serial<<"Writing "<<bufor[pos2]-48<<" at " << pos + pos2 << "\n";
			}

			validate_whole_number();
			set_alphabet_on_curpos();
			m_cur_digit_bak = m_button_typer.GetLetter(m_button_typer.CurrentPos());
			return true;
		}
		return false;
	}

	void SetCallback_DrawLetterAt(ButtonTyper<uint8_t>::DrawLetterAtCallback draw_letter_at_callback) {
		m_button_typer.SetCallback_DrawLetterAt(draw_letter_at_callback);
	}

	void validate_whole_number(){
		for(int pos=0;pos<m_button_typer.MaxTextSize();pos++){
			uint8_t max_number_ascii = m_max_number_chars[pos];
//			Serial<<"m_button_typer.GetLetter(pos): "<<m_button_typer.GetLetter(pos);
//			Serial<<", max_number_ascii: "<<max_number_ascii<<"\n";
			if (m_button_typer.GetLetter(pos) > max_number_ascii) {
//				Serial<<"Resetting digit on pos "<<pos<<" from " << m_button_typer.GetLetter(pos) << " to ";
				m_button_typer.SetLetter(pos, max_number_ascii-48);
//				Serial<<m_button_typer.GetLetter(pos)<<".\n";
			} else if (m_button_typer.GetLetter(pos) < max_number_ascii) {
				break;
			}
		}
	}

	uint8_t* debug_ReturnAlphabet() {return m_alphabet;}

private:

	ButtonTyper<uint8_t> m_button_typer;
	uint8_t* m_alphabet;
	uint32_t m_max_number;
	uint8_t* m_max_number_chars; //Max value possible to display in characters.
	uint8_t m_cur_digit_bak; //last value of the current digit

	void make_alphabet() {
		m_alphabet = new uint8_t[10];
		uint8_t i=0;
		for(;i<10;i++) {
			m_alphabet[i]=48+i;
		}
	}

	void count_max_value_chars() {
		m_max_number_chars = new uint8_t[m_button_typer.MaxTextSize()+1];
		itoa(m_max_number, reinterpret_cast<char*>(m_max_number_chars), 10);
	}

	void set_alphabet_on_curpos() {
		bool max_so_far = true;
		uint8_t pos=0;
		for(;pos<=m_button_typer.CurrentPos()-1;pos++){
			if (m_max_number_chars[pos] > m_button_typer.GetLetter(pos)) {
				max_so_far = false;
				break;
			}
		}
		if (max_so_far) {
			m_button_typer.SetAlphabetAtPos(m_alphabet, m_max_number_chars[pos]-47, pos);
		} else {
			m_button_typer.SetAlphabetAtPos(m_alphabet, 10, m_button_typer.CurrentPos());
		}
	}


};


